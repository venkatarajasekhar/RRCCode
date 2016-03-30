#ifndef KALMANFILTER_H
#define KALMANFILTER_H
#include "RRCCore/Field.h"
#include <vector>
#include "RRCCore/Sensor.h"
class Node;

class KalmanFilter
{
public:
    KalmanFilter(const Field &field, const Sensor &sensor);

    /**
     * @brief estimationUncertainty
     * ssca + sda algorithm
     *
     * reference: E. K.-W. Chu, H.-Y. Fan, W.-W. Lin, C.-S. Wang,
     * "Structure-Preserving Algorithms for Periodic Discrete-Time Algebraic
     * Riccati Equations",International Journal of Control,Vol. 77, Iss.8, 2004
     * @param movingSensorPath
     * @return
     */
    float estimationUncertainty(const std::vector<Node *> &movingSensorPath) const;

private:
    Field m_field;
    Sensor m_sensor;
    const float m_calculateUncerntaintyTolerance;
    void infoCollectedAlongPath(const std::vector<Node *> &movingSensorPath, std::vector<Eigen::MatrixXf> &infoMatrix) const;
};

#endif // KALMANFILTER_H
