#include "KalmanFilter.h"
#include "Sensor.h"
#include "RRCCommon/Node.h"
#include "RRCCommon/EigenVectorXdUtil.h"

KalmanFilter::KalmanFilter(const Field &field, const Sensor &sensor) : m_field(field), m_sensor(sensor), m_calculateUncerntaintyTolerance(0.001) {

}

float KalmanFilter::estimationUncertainty(const std::vector<Node *> &movingSensorPath) const {
    std::vector<Eigen::MatrixXd> infoCollected;
    infoCollectedAlongPath(movingSensorPath, infoCollected);
    if (infoCollected.size() == 0) throw std::invalid_argument("No info collected for Kalman filter!");

    // get A, Q, R;
    Eigen::MatrixXd A = m_field.A(), Q = m_field.Q();
    Eigen::MatrixXd H = Q;
    unsigned int infoMatrixDim = infoCollected.back().rows();
    Eigen::MatrixXd R = Eigen::MatrixXd::Identity(infoMatrixDim, infoMatrixDim) * m_sensor.R();

    // Get G
    int dimA = A.rows();
    int dimG = dimA, dimH = dimA;
    int period = infoCollected.size();

    std::vector<Eigen::MatrixXd> G;
    for(std::vector<Eigen::MatrixXd>::const_iterator iter = infoCollected.begin(); iter != infoCollected.end(); ++iter) {
        G.push_back((*iter).transpose() * R.inverse() * (*iter));
    }

    // transpose A
    A.transposeInPlace(); // node A becomes its transpose. In Eigen, do NOT do this A=A.transpose(), use A.transposeInPlace();
    // initialization
    std::vector<Eigen::MatrixXd> A_hat(2, Eigen::MatrixXd::Zero(dimA,dimA)), G_hat(2, Eigen::MatrixXd::Zero(dimG,dimG)), H_hat(2, Eigen::MatrixXd::Zero(dimH,dimH));

    A_hat[0] = A;
    G_hat[0] = G[0]; // G[0] always exist since the infoCollected is not empty
    H_hat[0] = H;

    Eigen::MatrixXd W(dimA,dimA), V1(dimA,dimA), V2(dimA,dimA);
    for(int i = 1; i < period; ++i) {
        W = Eigen::MatrixXd::Identity(dimA,dimA) + H * G_hat[0];
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
        W = Eigen::MatrixXd::Identity(dimG,dimG) + G_hat[0] * H_hat[0];
        A_hat[1] = A_hat[0] * (W.inverse() * A_hat[0]);
        G_hat[1] = G_hat[0] + A_hat[0] * ( G_hat[0] * (W.transpose()).inverse() ) * A_hat[0].transpose();
        H_hat[1] = H_hat[0] + A_hat[0].transpose() * (W.transpose()).inverse() * H_hat[0] * A_hat[0];

        if ((H_hat[1] - H_hat[0]).norm() <=  m_calculateUncerntaintyTolerance * H_hat[1].norm()) {
            break;
        } else {
            A_hat[0] = A_hat[1];
            G_hat[0] = G_hat[1];
            H_hat[0] = H_hat[1];
        }
    }

    // calculate the periodic solutions of the DARE
    // In order to save memory, here we use G to store the asymptotic covariance matrix. Here G is the PX in sscaSDA.m
    G[period-1] = H_hat[1];

    // transpose A back
    A.transposeInPlace();

    for (int i = period - 1; i > 0; --i) {
        G[i-1] = A * G[i] * A.transpose() - A * G[i] * infoCollected[i].transpose() * (infoCollected[i] * G[i] * infoCollected[i].transpose() + R).inverse() * infoCollected[i] * G[i] * A.transpose() + Q;
    }

    // get the cost
    float cost, specRadius;
    Eigen::VectorXcd eigenVal;
    Eigen::VectorXd real;
    eigenVal = G[0].eigenvalues();
    real = eigenVal.real();
    cost = EigenVectorXdUtil::max(real);

    for (int i = 1; i < period; i++) {
        eigenVal = G[i].eigenvalues();
        real = eigenVal.real();
        specRadius = EigenVectorXdUtil::max(real);
        if (specRadius > cost) {
            cost = specRadius;
        }
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

void KalmanFilter::infoCollectedAlongPath(const std::vector<Node *> &movingSensorPath, std::vector<Eigen::MatrixXd> &infoMatrix) const {
    infoMatrix.clear();
    for(std::vector<Node *>::const_iterator iter = movingSensorPath.begin(); iter != movingSensorPath.end(); ++iter) {
        Eigen::MatrixXd cMatrix = m_sensor.sensorMeasurementMatrix((*iter)->getPos(), m_field);
        infoMatrix.push_back(cMatrix);
    }
}

