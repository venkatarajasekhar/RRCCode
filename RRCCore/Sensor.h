#ifndef SENSOR_H
#define SENSOR_H
#include "Packages/Eigen/Core"
class Position;
class Field;

/**
 * @brief The Sensor class: scalar output sensor
 */
class Sensor
{
public:
    Sensor(float sensingRange, float sensorOutputScale, float sensorNoise);

    Eigen::MatrixXf sensorMeasurementMatrix(const Position &sensorPos, const Field &field) const;
    float R() const;

private:
    float m_sensingRange;
    float m_sensorOutputScale;
    float m_R; // sensor noise
};

#endif // SENSOR_H
