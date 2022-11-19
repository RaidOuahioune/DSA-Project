#ifndef BST_H
#define BST_H

#include <iostream>
#include <string.h>

#include "../Interfaces/Patient.h"
#include "../Interfaces/MedicalInfo.h"
#include "../utilities/FileHandler.h"

class BSTNode
{
private:
    BSTNode *right;
    BSTNode *left;
    Patient data;

    friend class BST;

public:
    BSTNode(const Patient &info, BSTNode *r = nullptr, BSTNode *l = nullptr)
        : right(r), left(l), data(info) {}
    BSTNode(Patient &&info, BSTNode *r = nullptr, BSTNode *l = nullptr)
        : right(r), left(l), data(std::move(info)) {}
};

class BST
{
public:
    void storeAllPatients();
    void insert(const Patient &);
    void insert(Patient &&);
    bool contains(const string &);
    void Delete(const string &, bool &state);
    int getNumberOfPatient() const;
    bool update(const string &, const MedicalInfo &);
    void InsertSortedArray(const vector<Patient> &);
    bool printPatient(const string &) const;
    BST(){};
    ~BST();

private:
    BSTNode *root = nullptr;
    int numberOfPatient = 0;
    void storeAllPatientsHelper(BSTNode *&);
    void InsertElementHelper(BSTNode *&, const Patient &);
    void InsertElementHelper(BSTNode *&, Patient &&);
    bool BinarySearchHelper(BSTNode *&, const string &) const;
    void DestructorHelper(BSTNode **);
    void Delete(const string &, BSTNode *&, bool &state);
    bool updateHelper(BSTNode *&, const string &, const MedicalInfo &);
    void InsertSortedArrayHelper(BSTNode *&, const vector<Patient> &, int, int);
    BSTNode *findMin(BSTNode *&root) const;
    void storeData(const Patient &patient) const;
    bool printPatient(const string &, BSTNode *) const;
};
int BST::getNumberOfPatient() const
{
    return this->numberOfPatient;
}

void BST::storeAllPatients()
{
    storeAllPatientsHelper(this->root);
}

void BST::storeAllPatientsHelper(BSTNode *&root)
{
    if (root == nullptr)
        return;
    storeAllPatientsHelper(root->left);
    storeData(root->data);
    storeAllPatientsHelper(root->right);
}

void BST::insert(const Patient &patient)
{
    InsertElementHelper(this->root, patient);
}
void BST::insert(Patient &&patient)
{
    InsertElementHelper(this->root, std::move(patient));
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
    else if (root->data < patient)
        InsertElementHelper(root->right, patient);
    else if (root->data > patient)
        InsertElementHelper(root->left, patient);
    else
    {
        cout << "PATIENT WITH THIS ID: " << patient.getId() << " ALREADY EXISTS" << endl;
        root->data.setMedicalInfo(patient.getMedicalInfo());
        cout << "THE PATIENT'S INFORMATION ENTERED HAS BEEN UPDATED "
             << endl;
        return;
    }
}

void BST::InsertElementHelper(BSTNode *&root, Patient &&patient)
{
    if (root == nullptr)
    {
        root = new BSTNode(std::move(patient));
        numberOfPatient++;
    }
    else if (root->data < patient)
        InsertElementHelper(root->right, std::move(patient));
    else
        InsertElementHelper(root->left, std::move(patient));
}
void BST::Delete(const string &value, bool &state)
{
    Delete(value, this->root, state);
}

BSTNode *BST::findMin(BSTNode *&root) const
{
    if (root == nullptr)
        return nullptr;
    if (root->left == nullptr)
        return root;
    return findMin(root->left);
}
void BST::Delete(const string &ID, BSTNode *&root, bool &state)
{
    if (root == nullptr)
        return; // Item not found; do nothing

    if (stoll(ID) < stoll(root->data.getId()))
        Delete(ID, root->left, state);
    else if (stoll(root->data.getId()) < stoll(ID))
        Delete(ID, root->right, state);
    else if (root->left != nullptr && root->right != nullptr) // Two children
    {
        root->data = findMin(root->right)->data;
        Delete(root->data.getId(), root->right, state);
    }
    else
    {
        BSTNode *oldNode = root;
        root = (root->left != nullptr) ? root->left : root->right;
        delete oldNode;
        numberOfPatient--;
        state = true;
    }
}

bool BST::update(const string &ID, const MedicalInfo &info)
{
    return updateHelper(root, ID, info);
}

bool BST::updateHelper(BSTNode *&root, const string &ID, const MedicalInfo &info)
{
    if (root == nullptr)
    {
        return false;
    }
    else
    {
        if (root->data.getId() == ID)
        {
            root->data.setMedicalInfo(info);
            return true;
        }
        else if (stoll(root->data.getId()) < stoll(ID))
            return updateHelper(root->right, ID, info);
        else
            return updateHelper(root->left, ID, info);
    }
}

void BST::InsertSortedArray(const vector<Patient> &vec)
{
    numberOfPatient = vec.size();
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
void BST::storeData(const Patient &patient) const
{
    FileHandler handler;
    if (is_file_exist("Data/" + patient.getId() + ".txt"))
        handler.InsertMedicalInfo(patient.getMedicalInfo(), patient.getId());
    else
        handler.InsertFullData(patient);
}

bool BST::printPatient(const string &ID, BSTNode *t) const
{
    if (t == nullptr)
        return false;
    else if (stoll(ID) < stoll(t->data.getId()))
        return printPatient(ID, t->left);
    else if (stoll(t->data.getId()) < stoll(ID))
        return printPatient(ID, t->right);
    else
    {
        t->data.printPatient();
        return true; // Match
    }
    return true;
}

bool BST::printPatient(const string &ID) const
{
    return printPatient(ID, root);
}

#endif