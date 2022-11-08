#ifndef BST_H
#define BST_H

#include <iostream>
#include <string.h>

#include "../Interfaces/Patient.h"
#include "../Interfaces/MedicalInfo.h"

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
    void InsertSortedArray(const vector<Patient> &);
    BST(){};
    ~BST();

private:
    BSTNode *root = nullptr;
    int numberOfPatient = 0;
    void InOrderHelper(BSTNode *&);
    void InsertElementHelper(BSTNode *&, const Patient &);
    bool BinarySearchHelper(BSTNode *&, const string &) const;
    void DestructorHelper(BSTNode **);
    void deletehelper(BSTNode *&, const string &);
    void updateHelper(BSTNode *&, const string &, const MedicalInfo &);
    void InsertSortedArrayHelper(BSTNode *&, const vector<Patient> &, int, int);
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
        else if (stoll(root->data.getId()) > stoll(id))
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

    if (stoll(root->data.getId()) > stoll(value))
        deletehelper(root->left, value);
    else if (stoll(root->data.getId()) < stoll(value))
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

void BST::updateHelper(BSTNode *&root, const string &ID, const MedicalInfo &info)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        if (root->data.getId() == ID)
            root->data.setMedicalInfo(info);
        else if (stoll(root->data.getId()) < stoll(ID))
            updateHelper(root->right, ID, info);
        else
            updateHelper(root->left, ID, info);
    }
}

void BST::InsertSortedArray(const vector<Patient> &vec)
{
    this->InsertSortedArrayHelper(this->root, vec, 0, vec.size() - 1);
}

void BST::InsertSortedArrayHelper(BSTNode *&root, const vector<Patient> &array, int left, int right)
{
    if (left > right)
        return;
    if (right == left)
    {
        root = new BSTNode(array[(left + right) / 2]);
        return;
    }
    else
    {
        int middle = (right + left) / 2;

        root = new BSTNode(array[middle]);
        InsertSortedArrayHelper(root->left, array, left, middle - 1); // it's like we have deleted the middle from the list when we are done inserting that node
        InsertSortedArrayHelper(root->right, array, middle + 1, right);
    }
}
#endif