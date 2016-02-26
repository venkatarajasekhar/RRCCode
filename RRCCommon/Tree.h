#ifndef TREE_H
#define TREE_H

#include <memory>
#include <vector>

class Node;

class Tree
{
public:
    Tree();
    virtual ~Tree();

    /**
     * @brief insert
     * @param newNode
     */
    virtual void insert(Node *newNode)=0;

    Node *getRoot() const;

protected:
    void setRoot(Node *root);
    Node *m_root;
};

#endif // TREE_H
