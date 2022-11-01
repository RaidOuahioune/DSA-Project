#ifndef BST_H
#define BST_H

#include <iostream>
#include <string.h>
#include "../Interfaces/Patient.h"
#include "../Interfaces/MedicalInfo.h"

using namespace std;

class BSTNode
{
private:
    BSTNode *right;
    BSTNode *left;
    Patient data;
    friend class BST;

public:
    BSTNode(const Patient info, BSTNode *r = nullptr, BSTNode *l = nullptr)
        : right(r), left(l), data(info) {}
};

class BST
{
public:
    void InOrder();
    void InsertElement(const Patient &);
    bool BinarySearch(const Patient &);
    void deleteElement(const Patient &);
    int getNumberOnNodes() const;
    void update(const string &, const MedicalInfo &);
    BST(){};
    ~BST();

private:
    BSTNode *root = nullptr;
    int numberOfNodes = 0;
    void InOrderHelper(BSTNode *&);
    void InsertElementHelper(BSTNode *&, const Patient &);
    bool BinarySearchHelper(BSTNode *&, const Patient &);
    void DestructorHelper(BSTNode **);
    void deleteElementhelper(BSTNode *&root, const Patient &);
    Patient getMin(BSTNode *&root);
};
int BST::getNumberOnNodes() const
{
    return this->numberOfNodes;
}

void BST::InOrder()
{
    InOrderHelper(this->root);
}

void BST::InOrderHelper(BSTNode *&root)
{
    if (root == nullptr)
        return;
    InOrderHelper(root->left);
    root->data.printPatient();
    InOrderHelper(root->right);
}

void BST::InsertElement(const Patient &a)
{
    InsertElementHelper(this->root, a);
}

bool BST::BinarySearchHelper(BSTNode *&root, const Patient &other)
{
    if (root == nullptr)
        return false;
    else
    {
        if (root->data == other)
            return true;
        else if (root->data > other)
            return BinarySearchHelper(root->left, other);
        else
            return BinarySearchHelper(root->right, other);
    }
}

bool BST::BinarySearch(const Patient &a)
{
    return BinarySearchHelper(this->root, a);
}

void BST::DestructorHelper(BSTNode **root) // equivalent to make empty()
{
    if (*(root) == nullptr)
        return;
    else
    {
        DestructorHelper(&((*root)->left));
        DestructorHelper(&((*root)->right));
        delete (*root);
        *root = nullptr;
    }
    numberOfNodes = 0;
};

BST::~BST()
{
    DestructorHelper(&(this->root));
}

void BST::InsertElementHelper(BSTNode *&root, const Patient &a)
{
    if (root == nullptr)
    {
        root = new BSTNode(a);
        numberOfNodes++;
    }
    else
    {
        if (root->data == a)
        {
            cout << "No Duplicated Data is alowed" << endl;

            return;
        }
        else if (root->data < a)
        {
            InsertElementHelper(root->right, a);
        }
        else
        {
            InsertElementHelper(root->left, a);
        }
    }
}
void BST::deleteElement(const Patient &value)
{
    deleteElementhelper(this->root, value);
}

Patient BST::getMin(BSTNode *&root)
{
    if (root == nullptr)
    {
        throw "exception";
    }
    else if (root->left == nullptr && root->right == nullptr)
    {
        return root->data;
    }
    else
    {
        return getMin(root->left);
    }
}
void BST::deleteElementhelper(BSTNode *&root, const Patient &value)
{
    if (root == nullptr)
        return;

    if (root->data > value)
        deleteElementhelper(root->left, value);
    else if (root->data < value)
        deleteElementhelper(root->right, value);

    else
    { // if elemnt is a leaf

        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            root = nullptr;
        }
        else if (root->left == nullptr) // one child only
        {

            BSTNode *temp = root->right;
            delete root;
            root = temp;
        }
        else if (root->right == nullptr)
        {
            BSTNode *temp = root->left;
            delete root;
            root = temp;
        }
        else
        { // elemnt is a full node
            // 1 search for the min value in the right subtree
            root->data = getMin(root->right);
            // 2 delete that value
            deleteElementhelper(root->right, root->data);
        }
    }
}

#endif