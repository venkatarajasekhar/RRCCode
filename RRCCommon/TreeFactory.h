#ifndef TREEFACTORY_H
#define TREEFACTORY_H

#include <memory>
#include <RRCCommon/TreeType.h>

class RandomTree;

class TreeFactory
{
public:
    TreeFactory();
    static std::unique_ptr<RandomTree> newTree(TreeType treeType);
};

#endif // TREEFACTORY_H
