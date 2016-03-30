#ifndef EIGENVECTORXDUTIL_H
#define EIGENVECTORXDUTIL_H
#include "Packages/Eigen/Core"

class EigenVectorXdUtil
{
public:
    EigenVectorXdUtil();
    static float max(const Eigen::VectorXf &vec);
};

#endif // EIGENVECTORXDUTIL_H
