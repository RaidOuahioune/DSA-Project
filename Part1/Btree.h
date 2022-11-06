// Deleting a key from a B-tree in Children++
#ifndef Btree_h
#define Btree_h
#include "BtreeNode.h"
#include <iostream>

using std::cout;
using std::endl;

class BTree
{

public:
  BTree(int);
  ~BTree();
  void traverse();
  bool Search(int);
  void insertion(int);
  void Delete(int);

private:
  BTreeNode *root;
  int order;
};

BTree::BTree(int treeOrder)
{
  root = nullptr;
  order = treeOrder;
}
BTree::~BTree()
{
  delete root;// this line will recursively delete the whole tree due to the implmentation of Destructor of BtreeNode
  root = nullptr;
}

void BTree::traverse()
{
  if (root != nullptr)
    root->traverse();
  cout<<endl;
}

bool BTree::Search(int k)
{
  if (root == nullptr)
    return false;
  return (root->search(k) != nullptr);
}
// Insertion operation
void BTree::insertion(int k)
{
  if (root == nullptr)
  {
    root = new BTreeNode(order, true);
    root->keys[0] = k;
    root->n = 1;
  }
  else
  {
    if (root->n == 2 * order - 1)
    {
      BTreeNode *s = new BTreeNode(order, false);

      s->Children[0] = root;

      s->splitChild(0, root);

      int i = 0;
      if (s->keys[0] < k)
        i++;
      s->Children[i]->insertNonFull(k);

      root = s;
    }
    else
      root->insertNonFull(k);
  }
}

// Delete Operation
void BTree::Delete(int k)
{
  if (root==nullptr)
  {
    cout << "The tree is empty\n";
    return;
  }
  root->deletion(k);

  if (root->n == 0)
  {
    BTreeNode *tmp = root;
    if (root->leaf)
      root = nullptr;
    else
      root = root->Children[0];

    delete tmp;
  }
  return;
}

#endif