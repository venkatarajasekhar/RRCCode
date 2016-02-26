#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include "NodeType.h"
#include <memory>

class Node;

class NodeFactory
{
public:
    static std::unique_ptr<Node> NewNode(NodeType nodeType);
};

#endif // NODEFACTORY_H
