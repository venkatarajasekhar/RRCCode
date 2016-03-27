#ifndef KDTREEWRAPPER_H
#define KDTREEWRAPPER_H

class KdTree;

class KdTreeWrapper
{
public:
    KdTreeWrapper(KdTree *kdTree);
    KdTree *getKdTree() const;
    static KdTreeWrapper *instance();

private:
    KdTree *m_KdTree;
    static KdTreeWrapper *ms_instance;
};

#endif // KDTREEWRAPPER_H
