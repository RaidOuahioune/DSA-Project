#ifndef BtreeNode_h
#define BtreeNode_h
#include <iostream>
using std::cout;
using std::endl;
class BTreeNode
{
public:
  BTreeNode(int treeOrder, bool isLeaf);
  ~BTreeNode();
  void traverse();
  int findKey(int k);
  BTreeNode *search(int k);
  void insertNonFull(int k);
  void splitChild(int i, BTreeNode *y);
  void deletion(int k);
  void removeFromLeaf(int index);
  void removeFromNonLeaf(int index);
  int getPredecessor(int index);
  int getSuccessor(int index);
  void fill(int index);
  void borrowFromPrev(int index);
  void borrowFromNext(int index);
  void merge(int index);

private:
  int *keys;
  int order;
  BTreeNode **Children;
  int n;
  bool leaf;
  friend class BTree;
};

BTreeNode::BTreeNode(int TreeOrder, bool leaf1)
{
  order = TreeOrder;
  leaf = leaf1;

  keys = new int[2 * order - 1];
  Children = new BTreeNode *[2 * order];

  n = 0;
}
BTreeNode::~BTreeNode()
{
  for (int y = 0; y < n; y++)
  {
    cout << keys[y] << "  ";
  }
  cout << endl;

  delete[] keys;
  // this loop is mendatory to avoid memory leaks and It defines a recursive Destruction of Nodes
  for (int i = 0; i <= n; ++i)
  {
    delete Children[i];
  }
  delete[] Children;
}
void BTreeNode::traverse()
{
  int i;
  for (i = 0; i < n; i++)
  {
    if (leaf == false)
      Children[i]->traverse();
    cout << " " << keys[i];
  }
  if (leaf == false)
    Children[i]->traverse();
}

// Find the key
int BTreeNode::findKey(int k)
{
  int index = 0;
  while (index < n && keys[index] < k)
    ++index;
  return index;
}

// Recursive Search
BTreeNode *BTreeNode::search(int k)
{
  int i = 0;
  // search k in the sorted array(ascending) of keys where n is the current number of keys in the node
  while (i < n && k > keys[i])
  {
    i++;
  }
  if (i < n && keys[i] == k)
  {
    return this; // return node cuz it contains the k
  }
  // at this point we have travesred all the node which means elemnt is not found
  // if current is leaf that means we won't find the elemnet anywhere else we search at the i th subtree
  return leaf ? nullptr : Children[i]->search(k);
}

// Insertion non full
void BTreeNode::insertNonFull(int k)
{
  int index = findKey(k);
  if (index < n && keys[index] == k)
  {
    cout << k << " ALREADY EXISTS" << endl;
    return;
  }
  int i = n - 1;

  if (leaf == true)
  {
    while (i >= 0 && keys[i] > k)
    {

      keys[i + 1] = keys[i];
      i--;
    }

    keys[i + 1] = k;
    n = n + 1;
  }
  else
  {
    while (i >= 0 && keys[i] > k)
      i--;

    if (Children[i + 1]->n == 2 * order - 1)
    {
      splitChild(i + 1, Children[i + 1]);

      if (keys[i + 1] < k)
        i++;
    }
    Children[i + 1]->insertNonFull(k);
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
void BTreeNode::deletion(int k)
{
  int index = findKey(k);

  if (index < n && keys[index] == k) // it means that we found the k in the array of keys of the node that have called this node
  {
    if (leaf)
      removeFromLeaf(index);
    else
      removeFromNonLeaf(index);
  }
  else
  {
    if (leaf)
    {
      cout << "The key " << k << " is does not exist in the tree\n";
      return;
    }

    bool flag = ((index == n) ? true : false);

    if (Children[index]->n < order)
      fill(index);

    if (flag && index > n)
      Children[index - 1]->deletion(k);
    else
      Children[index]->deletion(k);
  }
  return;
}

// Remove from the leaf
void BTreeNode::removeFromLeaf(int index)
{
  for (int i = index + 1; i < n; ++i)
    keys[i - 1] = keys[i];

  n--;

  return;
}

// Delete from non leaf node
void BTreeNode::removeFromNonLeaf(int index)
{
  int k = keys[index];

  if (Children[index]->n >= order)
  {
    int pred = getPredecessor(index);
    keys[index] = pred;
    Children[index]->deletion(pred);
  }

  else if (Children[index + 1]->n >= order)
  {
    int succ = getSuccessor(index);
    keys[index] = succ;
    Children[index + 1]->deletion(succ);
  }

  else
  {
    merge(index);
    Children[index]->deletion(k);
  }
  return;
}

int BTreeNode::getPredecessor(int index)
{
  BTreeNode *cur = Children[index];
  while (!cur->leaf)
    cur = cur->Children[cur->n];

  return cur->keys[cur->n - 1];
}

int BTreeNode::getSuccessor(int index)
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

  delete (sibling);
  sibling = nullptr;
  return;
}

#endif