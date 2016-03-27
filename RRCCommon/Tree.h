#ifndef TREE_H
#define TREE_H

#include <memory>
#include <vector>

class Node;

class Tree {
  public:
    Tree();
    virtual ~Tree();

    Node *getRoot() const;

  protected:
    void setRoot(Node *root);
    Node *m_root;
};

#endif // TREE_H
