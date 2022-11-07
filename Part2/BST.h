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
    void insert(const Patient &);
    bool contains(const string &);
    void Delete(const string &);
    int getNumberOfPatient() const;
    void update(const string &, const MedicalInfo &);
    BST(){};
    ~BST();

private:
    BSTNode *root = nullptr;
    int numberOfPatient = 0;
    void InOrderHelper(BSTNode *&);
    void InsertElementHelper(BSTNode *&, const Patient &);
    bool BinarySearchHelper(BSTNode *&, const string &) const;
    void DestructorHelper(BSTNode **);
    void deletehelper(BSTNode *&root, const string &);
    void updateHelper(BSTNode *&root, const string &, const MedicalInfo &info);
    Patient getMin(BSTNode *&root);
};
int BST::getNumberOfPatient() const
{
    return this->numberOfPatient;
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

void BST::insert(const Patient &patient)
{
    InsertElementHelper(this->root, patient);
}

bool BST::BinarySearchHelper(BSTNode *&root, const string &id) const
{
    if (root == nullptr)
        return false;
    else
    {
        if (root->data.getId() == id)
            return true;
        else if (stol(root->data.getId()) > stol(id))
            return BinarySearchHelper(root->left, id);
        else
            return BinarySearchHelper(root->right, id);
    }
}

bool BST::contains(const string &id)
{
    return BinarySearchHelper(this->root, id);
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
    numberOfPatient = 0;
};

BST::~BST()
{
    DestructorHelper(&(this->root));
}

void BST::InsertElementHelper(BSTNode *&root, const Patient &patient)
{
    if (root == nullptr)
    {
        root = new BSTNode(patient);
        numberOfPatient++;
    }
    else
    {
        if (root->data == patient)
        {
            cout << "No Duplicated Data is alowed" << endl;

            return;
        }
        else if (root->data < patient)
        {
            InsertElementHelper(root->right, patient);
        }
        else
        {
            InsertElementHelper(root->left, patient);
        }
    }
}
void BST::Delete(const string &value)
{
    deletehelper(this->root, value);
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
void BST::deletehelper(BSTNode *&root, const string &value)
{
    if (root == nullptr)
        return;

    if (stol(root->data.getId()) > stol(value))
        deletehelper(root->left, value);
    else if (stol(root->data.getId()) < stol(value))
        deletehelper(root->right, value);

    else
    { // if elemnt is patient leaf

        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            root = nullptr;
            this->numberOfPatient--;
        }
        else if (root->left == nullptr) // one child only
        {

            BSTNode *temp = root->right;
            delete root;
            root = temp;
            this->numberOfPatient--;
        }
        else if (root->right == nullptr)
        {
            BSTNode *temp = root->left;
            delete root;
            root = temp;
            this->numberOfPatient--;
        }
        else
        { // elemnt is patient full node
            // 1 search for the min value in the right subtree
            root->data = getMin(root->right);
            // 2 Delete that value
            deletehelper(root->right, root->data.getId());
        }
    }
}

void BST::update(const string &ID, const MedicalInfo &info)
{
    updateHelper(root, ID, info);
}

void BST::updateHelper(BSTNode &*root, const string &ID, const MedicalInfo &info)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        if (root->element.getId() == ID)
            root->element.setMedicalInfo(info);
        else if (stol(root->element.getId()) < stol(ID))
            update(root->right, ID, info);
        else
            update(root->left, ID, info);
    }
}

#endif