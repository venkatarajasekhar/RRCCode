#include "KdTreeWrapper.h"
#include "KdTree.h"

KdTreeWrapper *KdTreeWrapper::ms_instance = nullptr;

KdTreeWrapper::KdTreeWrapper(KdTree *kdTree) : m_KdTree(kdTree)
{
    ms_instance = this;
}

KdTreeWrapper *KdTreeWrapper::instance()
{
    return ms_instance;
}

KdTree *KdTreeWrapper::getKdTree() const
{
    return m_KdTree;
}


