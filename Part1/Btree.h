// Leader Full Name: Ouahioune Raid Abderrezak 

//Group:4

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
  BTree &operator=(const BTree &rhs);
  BTree &operator=(BTree &&rhs);
  ~BTree();
  void storeAllPatients();
  bool contains(const string &);
  bool insert(const Patient &);
  bool insert(Patient &&);
  void Delete(const string &, bool &state);
  bool update(const string &, const MedicalInfo &);
  bool update(const string &, const char &, Patient &);
  bool update(const string &, const char &, MedicalInfo &);
  int getNumberOfPatient() const;
  void InsertSortedArray(const vector<Patient> &);
  bool printPatient(const string &);

private:
  BTreeNode *root;
  int order;
  int numberOfPatient;
};

BTree::BTree(int treeOrder = NUMBER_OF_DEPARTMENTS)
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

void BTree::storeAllPatients()
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
bool BTree::insert(const Patient &patient)
{
  if (root == nullptr)
  {
    root = new BTreeNode(order, true);
    root->keys[0] = patient;
    root->n = 1;
    numberOfPatient++;
    return true;
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
      return s->Children[i]->insertNonFull(patient, numberOfPatient);

      root = s;
    }
    else
      return root->insertNonFull(patient, numberOfPatient);
  }
}

bool BTree::insert(Patient &&patient)
{
  if (root == nullptr)
  {
    root = new BTreeNode(order, true);
    root->keys[0] = std::move(patient);
    root->n = 1;
    return true;
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
      return s->Children[i]->insertNonFull(std::move(patient), numberOfPatient);

      root = s;
    }
    else
      return root->insertNonFull(std::move(patient), numberOfPatient);
  }
}

// Delete Operation
void BTree::Delete(const string &ID, bool &state)
{
  if (root == nullptr)
  {
    cout << "The tree is empty\n";
    return;
  }
  root->deletion(ID, numberOfPatient, state);

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

bool BTree::update(const string &ID, const MedicalInfo &info)
{
  if (root != nullptr)
  {
    return root->update(ID, info);
  }
  else
    return false;
}
bool BTree::update(const string &ID, const char &dep, Patient &info)
{
  if (root != nullptr)
  {
    return root->update(ID, dep, info);
  }
  else
    return false;
}
bool BTree::update(const string &ID, const char &dep, MedicalInfo &info)
{
  if (root != nullptr)
  {
    return root->update(ID, dep, info);
  }
  else
    return false;
}
int BTree::getNumberOfPatient() const
{
  return this->numberOfPatient;
}

BTree &BTree::operator=(const BTree &rhs)
{
  this->order = rhs.order;
  this->numberOfPatient = rhs.numberOfPatient;
  this->root = rhs.root;
  return (*this);
}
BTree &BTree::operator=(BTree &&rhs)
{
  this->order = rhs.order;
  this->numberOfPatient = rhs.numberOfPatient;
  this->root = rhs.root;
  delete rhs.root;
  return (*this);
}
void BTree::InsertSortedArray(const vector<Patient> &vec)
{

  numberOfPatient = vec.size();
  this->root->InsertSortedArrayHelper(root, vec);
}

bool BTree::printPatient(const string &ID)
{
  PatientFlag pf = this->root->Search(ID);

  if (pf.found)
  {
    pf.patient.printPatient();
    return true;
  }
  return false;
}

#endif