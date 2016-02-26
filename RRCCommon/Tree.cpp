#include "Tree.h"

Tree::Tree() : m_root(nullptr)
{

}

Tree::~Tree()
{

}

Node *Tree::getRoot() const
{
    return m_root;
}

void Tree::setRoot(Node *root)
{
    m_root = root;
}
