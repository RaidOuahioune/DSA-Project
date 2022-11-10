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
  bool contains(const string &);
  void insert(const Patient &);
  void insert(Patient &&);
  void Delete(const string &);
  void update(const string &, const MedicalInfo &);
  int getNumberOfPatient() const;

private:
  BTreeNode *root;
  int order;
  int numberOfPatient;
};

BTree::BTree(int treeOrder)
{
  root = nullptr;
  order = treeOrder;
  numberOfPatient = 0;
}
BTree::~BTree()
{
  delete root; // this line will recursively delete the whole tree due to the implmentation of Destructor of BtreeNode
  root = nullptr;
}

void BTree::traverse()
{
  if (root != nullptr)
    root->traverse();
  cout << endl;
}

bool BTree::contains(const string &ID)
{
  if (root == nullptr)
    return false;
  return (root->search(ID) != nullptr);
}
// Insertion operation
void BTree::insert(const Patient &patient)
{
  if (root == nullptr)
  {
    root = new BTreeNode(order, true);
    root->keys[0] = patient;
    root->n = 1;
    numberOfPatient++;
  }
  else
  {
    if (root->n == 2 * order - 1)
    {
      BTreeNode *s = new BTreeNode(order, false);

      s->Children[0] = root;

      s->splitChild(0, root);

      int i = 0;
      if (s->keys[0] < patient)
        i++;
      s->Children[i]->insertNonFull(patient, numberOfPatient);

      root = s;
    }
    else
      root->insertNonFull(patient, numberOfPatient);
  }
}

void BTree::insert(Patient &&patient)
{
  if (root == nullptr)
  {
    root = new BTreeNode(order, true);
    root->keys[0] = std::move(patient);
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
      if (s->keys[0] < patient)
        i++;
      s->Children[i]->insertNonFull(std::move(patient), numberOfPatient);

      root = s;
    }
    else
      root->insertNonFull(std::move(patient), numberOfPatient);
  }
}

// Delete Operation
void BTree::Delete(const string &ID)
{
  if (root == nullptr)
  {
    cout << "The tree is empty\n";
    return;
  }
  root->deletion(ID, numberOfPatient);

  if (root->n == 0)
  {
    BTreeNode *tmp = root;
    if (root->leaf)
      root = nullptr;
    else
      root = root->Children[0];

    delete (tmp);
    tmp = nullptr;
  }
  return;
}

void BTree::update(const string &ID, const MedicalInfo &info)
{
  if (root != nullptr)
  {
    root->update(ID, info);
  }
  else
    cout << "\nTree is Empty !You may want to Create a new Patient Instead" << endl;
}
int BTree::getNumberOfPatient() const
{
  return this->numberOfPatient;
}
#endif