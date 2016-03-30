#include "KalmanFilter.h"
#include "Sensor.h"
#include "RRCCommon/Node.h"
#include "RRCCommon/EigenVectorXdUtil.h"
#include <iostream> //TODO: remove later, used to debug
#include <chrono> //TODO: remove later, used to debug, find the time elapsed

KalmanFilter::KalmanFilter(const Field &field, const Sensor &sensor) : m_field(field), m_sensor(sensor), m_calculateUncerntaintyTolerance(0.5) {

}

float KalmanFilter::estimationUncertainty(const std::vector<Node *> &movingSensorPath) const {
    std::vector<Eigen::MatrixXf> infoCollected;
    infoCollectedAlongPath(movingSensorPath, infoCollected);
    if (infoCollected.size() == 0) throw std::invalid_argument("No info collected for Kalman filter!");

    // get A, Q, R;
    Eigen::MatrixXf A = m_field.A(), Q = m_field.Q();
    Eigen::MatrixXf H = Q;
    unsigned int infoMatrixDim = infoCollected.back().rows();
    Eigen::MatrixXf R = Eigen::MatrixXf::Identity(infoMatrixDim, infoMatrixDim) * m_sensor.R();

    // Get G
    int dimA = A.rows();
    int dimG = dimA, dimH = dimA;
    int period = infoCollected.size();

    std::vector<Eigen::MatrixXf> G;
    for(std::vector<Eigen::MatrixXf>::const_iterator iter = infoCollected.begin(); iter != infoCollected.end(); ++iter) {
        G.push_back((*iter).transpose() * R.inverse() * (*iter));
    }

    // transpose A
    A.transposeInPlace(); // node A becomes its transpose. In Eigen, do NOT do this A=A.transpose(), use A.transposeInPlace();
    // initialization
    std::vector<Eigen::MatrixXf> A_hat(2, Eigen::MatrixXf::Zero(dimA,dimA)), G_hat(2, Eigen::MatrixXf::Zero(dimG,dimG)), H_hat(2, Eigen::MatrixXf::Zero(dimH,dimH));

    A_hat[0] = A;
    G_hat[0] = G[0]; // G[0] always exist since the infoCollected is not empty
    H_hat[0] = H;

    Eigen::MatrixXf W(dimA,dimA), V1(dimA,dimA), V2(dimA,dimA);
    for(int i = 1; i < period; ++i) {
        W = Eigen::MatrixXf::Identity(dimA,dimA) + H * G_hat[0];
        V1 = W.inverse() * A.transpose();
        V2 = W.inverse() * H;
        A_hat[1] = V1.transpose() * A_hat[0];
        G_hat[1] = G[i] + A * G_hat[0] * V1;
        H_hat[1] = H_hat[0] + A_hat[0].transpose() * V2 * A_hat[0];

        A_hat[0] = A_hat[1];
        G_hat[0] = G_hat[1];
        H_hat[0] = H_hat[1];
    }

    // SDA algorithm
    A_hat[0] = A_hat[1];
    G_hat[0] = G_hat[1];
    H_hat[0] = H_hat[1];

    while (1) {
        W = Eigen::MatrixXf::Identity(dimG,dimG) + G_hat[0] * H_hat[0];
        A_hat[1] = A_hat[0] * (W.inverse() * A_hat[0]);
        G_hat[1] = G_hat[0] + A_hat[0] * ( G_hat[0] * (W.transpose()).inverse() ) * A_hat[0].transpose();
        H_hat[1] = H_hat[0] + A_hat[0].transpose() * (W.transpose()).inverse() * H_hat[0] * A_hat[0];

        if ((H_hat[1] - H_hat[0]).norm() <=  m_calculateUncerntaintyTolerance) {
            break;
        } else {
            A_hat[0] = A_hat[1];
            G_hat[0] = G_hat[1];
            H_hat[0] = H_hat[1];
        }
    }

    // calculate cycle cost, which is the largest spectral radius of all the asymptotic covariance matrix
    Eigen::MatrixXf currAsymCovMat = H_hat[1];
    // eigenvalues() return complex values even though the eigenvalues are real
    // float cost = EigenVectorXdUtil::max(currAsymCovMat.eigenvalues().real());
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXf> eigenSolver;
    eigenSolver.compute(currAsymCovMat);
    float cost = EigenVectorXdUtil::max(eigenSolver.eigenvalues());

    // transpose A back
    A.transposeInPlace();
    for (int i = period - 1; i > 0; --i) {
        currAsymCovMat = A * currAsymCovMat * A.transpose() - A * currAsymCovMat * infoCollected[i].transpose() * (infoCollected[i] * currAsymCovMat * infoCollected[i].transpose() + R).inverse() * infoCollected[i] * currAsymCovMat * A.transpose() + Q;
        eigenSolver.compute(currAsymCovMat);
        float specRadius = EigenVectorXdUtil::max(eigenSolver.eigenvalues());
        if (specRadius > cost) cost = specRadius;
    }

    return cost;

//    // average trace along one cycle
//    float cost=0;
//    for (int i = 0; i < period; ++i) {
//        cost = cost + G[i].trace();
//    }
//    cost = cost / (double)period;

//    return cost;
}

void KalmanFilter::infoCollectedAlongPath(const std::vector<Node *> &movingSensorPath, std::vector<Eigen::MatrixXf> &infoMatrix) const {
    infoMatrix.clear();
    for(std::vector<Node *>::const_iterator iter = movingSensorPath.begin(); iter != movingSensorPath.end(); ++iter) {
        Eigen::MatrixXf cMatrix = m_sensor.sensorMeasurementMatrix((*iter)->getPos(), m_field);
        infoMatrix.push_back(cMatrix);
    }
}

