#ifndef BtreeNode_h
#define BtreeNode_h
#include <iostream>
#include "../Interfaces/Patient.h"
using std::cout;
using std::endl;
class BTreeNode
{
public:
  BTreeNode(int treeOrder, bool isLeaf);
  ~BTreeNode();

private:
  // DATA MEMBERS

  Patient *keys;
  int order;
  BTreeNode **Children;
  int n;
  bool leaf;

  // UTILITY FUNCTIONS

  int findKey(const string &);
  BTreeNode *search(const string &);
  void insertNonFull(const Patient &, int &numberOfPatient);
  void insertNonFull(Patient &&, int &numberOfPatient);
  void splitChild(int i, BTreeNode *y);
  void deletion(const string &, int &numberOfPatient);
  void removeFromLeaf(int index, int &numberOfPatient);
  void removeFromNonLeaf(int index, int &numberOfPatient);
  Patient getPredecessor(int index);
  Patient getSuccessor(int index);
  void fill(int index);
  void borrowFromPrev(int index);
  void borrowFromNext(int index);
  void merge(int index);
  void traverse();
  void update(const string &ID, const MedicalInfo &info);
  friend class BTree;
};

BTreeNode::BTreeNode(int TreeOrder, bool leaf1)
{
  order = TreeOrder;
  leaf = leaf1;

  keys = new Patient[2 * order - 1];
  Children = new BTreeNode *[2 * order]
  { nullptr };

  n = 0;
}
BTreeNode::~BTreeNode()
{

  // this loop is mendatory to avoid memory leaks and It defines a recursive    Destruction of Nodes

  for (int i = 0; i < n; i++)
  {
    if (!leaf)
    {
      delete (Children[i]);
      Children[i] = nullptr;
    }
  }

  delete[] Children;
  delete[] keys;
}
void BTreeNode::traverse()
{
  int i;
  for (i = 0; i < n; i++)
  {
    if (leaf == false)
      Children[i]->traverse();
    keys[i].printPatient();
  }
  if (leaf == false)
    Children[i]->traverse();
}

// Find the key
int BTreeNode::findKey(const string &ID)
{
  int index = 0;
  while (index < n && stoll(keys[index].getId()) < stoll(ID))
    ++index;
  return index;
}

// Recursive Search
BTreeNode *BTreeNode::search(const string &ID)
{
  int i = 0;
  // search k in the sorted array(ascending) of keys where n is the current number of keys in the node
  while (i < n && (stoll(ID) > stoll(keys[i].getId())))
  {
    i++;
  }
  if (i < n && keys[i].getId() == ID)
  {
    return this; // return node cuz it contains the k
  }
  // at this point we have travesred all the node which means elemnt is not found
  // if current is leaf that means we won't find the elemnet anywhere else we search at the i th subtree
  return leaf ? nullptr : Children[i]->search(ID);
}

// Insertion non full
void BTreeNode::insertNonFull(const Patient &patient, int &numberOfPatient)
{
  int index = findKey(patient.getId());
  if (index < n && keys[index] == patient)
  {
    cout << "PATIENT WITH THIS ID: " << patient.getId() << " ALREADY EXISTS" << endl;
    return;
  }
  int i = n - 1;

  if (leaf == true)
  {
    while (i >= 0 && keys[i] > patient)
    {
      keys[i + 1] = keys[i];
      i--;
    }

    keys[i + 1] = patient;
    n = n + 1;
    numberOfPatient++;
  }
  else
  {
    while (i >= 0 && keys[i] > patient)
      i--;

    if (Children[i + 1]->n == 2 * order - 1)
    {
      splitChild(i + 1, Children[i + 1]);

      if (keys[i + 1] < patient)
        i++;
    }
    Children[i + 1]->insertNonFull(patient, numberOfPatient);
  }
}
void BTreeNode::insertNonFull(Patient &&patient, int &numberOfPatient)
{
  int index = findKey(patient.getId());
  if (index < n && keys[index] == std::move(patient))
  {
    cout << "PATIENT WITH THIS ID: " << patient.getId() << " ALREADY EXISTS" << endl;
    return;
  }
  int i = n - 1;

  if (leaf == true)
  {
    while (i >= 0 && keys[i] > patient)
    {
      keys[i + 1] = keys[i];
      i--;
    }

    keys[i + 1] = std::move(patient);
    n = n + 1;
    numberOfPatient++;
  }
  else
  {
    while (i >= 0 && keys[i] > patient)
      i--;

    if (Children[i + 1]->n == 2 * order - 1)
    {
      splitChild(i + 1, Children[i + 1]);

      if (keys[i + 1] < patient)
        i++;
    }
    Children[i + 1]->insertNonFull(std::move(patient), numberOfPatient);
  }
}
// Split child
void BTreeNode::splitChild(int i, BTreeNode *y)
{
  BTreeNode *z = new BTreeNode(y->order, y->leaf);
  z->n = order - 1;

  for (int j = 0; j < order - 1; j++)
    z->keys[j] = y->keys[j + order];

  if (y->leaf == false)
  {
    for (int j = 0; j < order; j++)
      z->Children[j] = y->Children[j + order];
  }

  y->n = order - 1;

  for (int j = n; j >= i + 1; j--)
    Children[j + 1] = Children[j];

  Children[i + 1] = z;

  for (int j = n - 1; j >= i; j--)
    keys[j + 1] = keys[j];

  keys[i] = y->keys[order - 1];

  n = n + 1;
}

// Traverse

// Deletion operation
void BTreeNode::deletion(const string &ID, int &numberOfPatient)
{
  int index = findKey(ID);

  if (index < n && keys[index].getId() == ID) // it means that we found the k in the array of keys of the node that have called this node
  {
    if (leaf)
      removeFromLeaf(index, numberOfPatient);
    else
      removeFromNonLeaf(index, numberOfPatient);
  }
  else
  {
    if (leaf)
    {
      cout << "The Patient with the ID: " << ID << " does not exist in the tree\n";
      return;
    }

    bool flag = ((index == n) ? true : false);

    if (Children[index]->n < order)
      fill(index);

    if (flag && index > n)
      Children[index - 1]->deletion(ID, numberOfPatient);
    else
      Children[index]->deletion(ID, numberOfPatient);
  }
  return;
}

// Remove from the leaf
void BTreeNode::removeFromLeaf(int index, int &numberOfPatient)
{
  for (int i = index + 1; i < n; ++i)
    keys[i - 1] = keys[i];

  n--;
  numberOfPatient--;

  return;
}

// Delete from non leaf node
void BTreeNode::removeFromNonLeaf(int index, int &numberOfPatient)
{
  string ID = keys[index].getId();

  if (Children[index]->n >= order)
  {
    Patient pred = getPredecessor(index);
    keys[index] = pred;
    Children[index]->deletion(pred.getId(), numberOfPatient);
  }

  else if (Children[index + 1]->n >= order)
  {
    Patient succ = getSuccessor(index);
    keys[index] = succ;
    Children[index + 1]->deletion(succ.getId(), numberOfPatient);
  }

  else
  {
    merge(index);
    Children[index]->deletion(ID, numberOfPatient);
  }
  return;
}

Patient BTreeNode::getPredecessor(int index)
{
  BTreeNode *cur = Children[index];
  while (!cur->leaf)
    cur = cur->Children[cur->n];

  return cur->keys[cur->n - 1];
}

Patient BTreeNode::getSuccessor(int index)
{
  BTreeNode *cur = Children[index + 1];
  while (!cur->leaf)
    cur = cur->Children[0];

  return cur->keys[0];
}

void BTreeNode::fill(int index)
{
  if (index != 0 && Children[index - 1]->n >= order)
    borrowFromPrev(index);

  else if (index != n && Children[index + 1]->n >= order)
    borrowFromNext(index);

  else
  {
    if (index != n)
      merge(index);
    else
      merge(index - 1);
  }
  return;
}

// Borrow from previous
void BTreeNode::borrowFromPrev(int index)
{
  BTreeNode *child = Children[index];
  BTreeNode *sibling = Children[index - 1];

  for (int i = child->n - 1; i >= 0; --i)
    child->keys[i + 1] = child->keys[i];

  if (!child->leaf)
  {
    for (int i = child->n; i >= 0; --i)
      child->Children[i + 1] = child->Children[i];
  }

  child->keys[0] = keys[index - 1];

  if (!child->leaf)
    child->Children[0] = sibling->Children[sibling->n];

  keys[index - 1] = sibling->keys[sibling->n - 1];

  child->n += 1;
  sibling->n -= 1;

  return;
}

// Borrow from the next
void BTreeNode::borrowFromNext(int index)
{
  BTreeNode *child = Children[index];
  BTreeNode *sibling = Children[index + 1];

  child->keys[(child->n)] = keys[index];

  if (!(child->leaf))
    child->Children[(child->n) + 1] = sibling->Children[0];

  keys[index] = sibling->keys[0];

  for (int i = 1; i < sibling->n; ++i)
    sibling->keys[i - 1] = sibling->keys[i];

  if (!sibling->leaf)
  {
    for (int i = 1; i <= sibling->n; ++i)
      sibling->Children[i - 1] = sibling->Children[i];
  }

  child->n += 1;
  sibling->n -= 1;

  return;
}

// Merge
void BTreeNode::merge(int index)
{
  BTreeNode *child = Children[index];
  BTreeNode *sibling = Children[index + 1];

  child->keys[order - 1] = keys[index];

  for (int i = 0; i < sibling->n; ++i)
    child->keys[i + order] = sibling->keys[i];

  if (!child->leaf)
  {
    for (int i = 0; i <= sibling->n; ++i)
      child->Children[i + order] = sibling->Children[i];
  }

  for (int i = index + 1; i < n; ++i)
    keys[i - 1] = keys[i];

  for (int i = index + 2; i <= n; ++i)
    Children[i - 1] = Children[i];

  child->n += sibling->n + 1;
  n--;
}

void BTreeNode::update(const string &ID, const MedicalInfo &info)
{
  int i = 0;
  // search k in the sorted array(ascending) of keys where n is the current number of keys in the node
  while (i < n && (stoll(ID) > stoll(keys[i].getId())))
  {
    i++;
  }
  if (i < n && keys[i].getId() == ID)
  {
    // once element is found update it
    keys[i].setMedicalInfo(info);

    return;
  }
  // at this point we have travesred all the node which means elemnt is not found
  // if current is leaf that means we won't find the elemnet anywhere else we search at the i th subtree
  if (leaf)
  { // if current node is  leaf it means we didn't find the elment (hence no update is done)
    cout << endl
         << "ID not Found!You may want to use Create a new patient Instead" << endl;
    return;
  } // otherwise traverse the subtree
  Children[i]->update(ID, info);
}

#endif