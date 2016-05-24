#ifndef EIGENVECTORXDUTIL_H
#define EIGENVECTORXDUTIL_H
namespace Eigen {
    class VectorXf;
}

class EigenVectorXdUtil
{
public:
    EigenVectorXdUtil();
    static float max(const Eigen::VectorXf &vec);
};

#endif // EIGENVECTORXDUTIL_H
