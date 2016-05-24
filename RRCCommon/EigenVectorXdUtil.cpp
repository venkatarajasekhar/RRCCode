#include "EigenVectorXdUtil.h"
#include "Packages/Eigen/Core"

EigenVectorXdUtil::EigenVectorXdUtil() {

}

float EigenVectorXdUtil::max(const Eigen::VectorXf &vec) {
    if (vec.size() == 0) throw std::invalid_argument("Calling to max of VectorXd, vector can not be empty");

    float maxElement = vec(0);
    for (int i = 1; i < vec.size(); ++i) {
        if(vec(i) > maxElement) {
            maxElement=vec(i);
        }
    }

    return maxElement;
}

