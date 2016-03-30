#ifndef FIELD_H
#define FIELD_H
#include "Packages/Eigen/Dense"
#include "RRCCommon/Position.h"
class Area;

class Field
{
public:
    Field();
    Field(const Area &sceneSize);

    Eigen::MatrixXf A() const;

    Eigen::MatrixXf Q() const;

    std::vector<Position> bases() const;
    unsigned int fieldDimension() const;

private:
    Eigen::MatrixXf m_A;
    Eigen::MatrixXf m_Q;
    std::vector<Position> m_bases;

    void initializeFieldFromConfig(const Area &sceneSize);

};

#endif // FIELD_H
