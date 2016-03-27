#include "Field.h"
#include "RRCConfig/RRCConfig.h"
#include <stdexcept>
#include "RRCCommon/LogUtil.h"
#include "RRCCommon/Area.h"
#include <sstream>

Field::Field() {
    m_A = Eigen::MatrixXd::Zero(3,3);
    m_Q = Eigen::MatrixXd::Zero(3,3);
}

Field::Field(const Area &sceneSize) {
    initializeFieldFromConfig(sceneSize);
}

Eigen::MatrixXd Field::A() const {
    return m_A;
}

Eigen::MatrixXd Field::Q() const {
    return m_Q;
}

std::vector<Position> Field::bases() const {
    return m_bases;
}

unsigned int Field::fieldDimension() const
{
    return m_bases.size();
}

void Field::initializeFieldFromConfig(const Area &sceneSize) {
    Eigen::MatrixXd defaultA = Eigen::MatrixXd::Identity(3,3) * 0.99;
    Eigen::MatrixXd defaultQ = Eigen::MatrixXd::Identity(3,3) * 4;

    try {
        m_A = RRCConfig::Instance()->initializeFromConfig("Field", "AMatrix", defaultA);
        m_Q = RRCConfig::Instance()->initializeFromConfig("Field", "QMatrix", defaultQ);
        m_bases = RRCConfig::Instance()->initializeBasesFromConfig();

        if (m_A.rows() != m_Q.rows() || m_A.rows() != m_bases.size()) throw std::invalid_argument("A matrix's dimension should be the same as the Q matrix's dimension and their dimension should be equal to the number of basis centers");

        for(std::vector<Position>::const_iterator iter = m_bases.begin(); iter != m_bases.end(); ++iter) {
            if(sceneSize.isInsideArea(*iter) == false) {
                std::stringstream ss;
                ss <<"Basis [" << iter->x() << ", " << iter->y() << "] is outside scene size [" << sceneSize.width() << ", " << sceneSize.height() << "]";
                throw std::invalid_argument(ss.str());
            }
        }

    } catch(const std::exception &exp) {
        LogUtil::error("Exceptions thrown while initializing field, " + std::string(exp.what()));
        m_A = defaultA;
        m_Q = defaultQ;

        // default basis position
        float width = sceneSize.width(), height = sceneSize.height();
        std::vector<Position> defaultBases;
        defaultBases.push_back(Position(width / 4, height / 4));
        defaultBases.push_back(Position(width * 3.0 / 4, height / 4));
        defaultBases.push_back(Position(width / 2, height * 3.0 / 4));

        m_bases = defaultBases;
    }
}





