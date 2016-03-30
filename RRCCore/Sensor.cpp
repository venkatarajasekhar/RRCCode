#include "Sensor.h"
#include "RRCCore/Field.h"
#include <math.h>

Sensor::Sensor(float sensingRange, float sensorOutputScale, float sensorNoise) : m_sensingRange(sensingRange), m_sensorOutputScale(sensorOutputScale) ,m_R(sensorNoise) {

}

Eigen::MatrixXf Sensor::sensorMeasurementMatrix(const Position &sensorPos, const Field &field) const {
    Eigen::MatrixXf cMatrix = Eigen::MatrixXf::Zero(1, field.fieldDimension());
    std::vector<Position> bases = field.bases();
    for(unsigned int i = 0; i < bases.size(); ++i) {
        cMatrix(0,i) = m_sensorOutputScale * exp( (-1.0) * sensorPos.distSquaredToOtherPos(bases[i])  / (2 * m_sensingRange * m_sensingRange));
    }

    return cMatrix;
}

float Sensor::R() const {
    return m_R;
}


