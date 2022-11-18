#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "../Interfaces/Patient.h"
#include <algorithm>
#include <iostream>
#include "../utilities/FileHandler.h"
using namespace std;

class AvlNode
{
public:
    AvlNode(const Patient &ele, AvlNode *lt, AvlNode *rt, int h = 0)
        : element{ele}, left{lt}, right{rt}, height{h} {}

    AvlNode(Patient &&ele, AvlNode *lt, AvlNode *rt, int h = 0)
        : element{std::move(ele)}, left{lt}, right{rt}, height{h} {}

private:
    Patient element;
    AvlNode *left;
    AvlNode *right;
    int height;

    friend class AvlTree;
};

class AvlTree
{
public:
    AvlTree() : root{nullptr}, NumberOfPatient(0)
    {
    }

    AvlTree(const AvlTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }

    AvlTree(AvlTree &&rhs) : root{rhs.root}
    {
        rhs.root = nullptr;
    }

    ~AvlTree()
    {
       
        makeEmpty();
    }

    /**
     * Deep copy.
     */
    AvlTree &operator=(const AvlTree &rhs)
    {
        AvlTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    /**
     * Move.
     */
    AvlTree &operator=(AvlTree &&rhs)
    {
        std::swap(root, rhs.root);

        return *this;
    }

    bool contains(const string &ID) const
    {
        return contains(ID, root);
    }

    bool isEmpty() const
    {
        return root == nullptr;
    }

    void storeAllPatients() const
    {
        if (isEmpty())
            cout << "Empty tree" << endl;
        else
            storeAllPatients(root);
    }

    void makeEmpty()
    {
        NumberOfPatient = 0;
        makeEmpty(root);
    }

    void insert(const Patient &ID)
    {

        insert(ID, root);
    }

    void insert(Patient &&ID)
    {
        insert(std::move(ID), root);
    }

    void update(const string &ID, const MedicalInfo &info)
    {
        update(root, ID, info);
    }

    /**
     * Remove ID from the tree. Nothing is done if ID is not found.
     */
    void Delete(const string &ID)
    {

        Delete(ID, root);
    }
    int getNumberOfPatient() const
    {
        return NumberOfPatient;
    }
    void InsertSortedArray(const vector<Patient> &vec)
    {
        NumberOfPatient = vec.size();
        this->InsertSortedArrayHelper(this->root, vec, 0, vec.size() - 1);
    }

private:
    AvlNode *root;
    static const int CAPACITY = 10000;
    int NumberOfPatient;

    void insert(const Patient &ID, AvlNode *&t)
    {

        if (t == nullptr)
        {
            t = new AvlNode{ID, nullptr, nullptr};
            NumberOfPatient++;
        }
        else if (ID < t->element)
            insert(ID, t->left);
        else if (t->element < ID)
            insert(ID, t->right);
        else
        {
            cout << "Patient Already exist Maybe you want to use update instead" << endl;
        }

        balance(t);
    }

    void insert(Patient &&ID, AvlNode *&t)
    {
        if (t == nullptr)
        {
            NumberOfPatient++;
            t = new AvlNode{std::move(ID), nullptr, nullptr};
        }
        else if (ID < t->element)
            insert(std::move(ID), t->left);
        else if (t->element < ID)
            insert(std::move(ID), t->right);

        balance(t);
    }

    void Delete(const string &ID, AvlNode *&t)
    {
        if (t == nullptr)
            return; // Item not found; do nothing

        if (stoll(ID) < stoll(t->element.getId()))
            Delete(ID, t->left);
        else if (stoll(t->element.getId()) < stoll(ID))
            Delete(ID, t->right);
        else if (t->left != nullptr && t->right != nullptr) // Two children
        {
            t->element = findMin(t->right)->element;
            Delete(t->element.getId(), t->right);
        }
        else
        {
            AvlNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
            NumberOfPatient--;
        }

        balance(t);
    }

    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);

        t->height = max(height(t->left), height(t->right)) + 1;
    }

    AvlNode *findMin(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    bool contains(const string &ID, AvlNode *t) const
    {
        if (t == nullptr)
            return false;
        else if (stoll(ID) < stoll(t->element.getId()))
            return contains(ID, t->left);
        else if (stoll(t->element.getId()) < stoll(ID))
            return contains(ID, t->right);
        else
            return true; // Match
        return true;
    }

    void makeEmpty(AvlNode *&t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    void storeAllPatients(AvlNode *t) const
    {
        if (t != nullptr)
        {
            storeAllPatients(t->left);
            this->storeData(t->element);
            storeAllPatients(t->right);
        }
    }

    AvlNode *clone(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new AvlNode{t->element, clone(t->left), clone(t->right), t->height};
    }

    int height(AvlNode *t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    void rotateWithLeftChild(AvlNode *&k2)
    {
        // PlZ Uncomment this line if you want to test InsertSortedArray()function that guarantes no balancing for the tree and Building in a linear time
        std::cout << "Warining There is A rotation" << std::endl;
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    void rotateWithRightChild(AvlNode *&k1)
    {
        //std::cout << "Warining There is A rotation" << std::endl;
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    void doubleWithLeftChild(AvlNode *&k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(AvlNode *&k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
    void update(AvlNode *&root, const string &ID, const MedicalInfo &info)
    {
        if (root == nullptr)
        {
            return;
        }
        else
        {
            if (root->element.getId() == ID)
                root->element.setMedicalInfo(info);
            else if (stoll(root->element.getId()) < stoll(ID))
                update(root->right, ID, info);
            else
                update(root->left, ID, info);
        }
    }

    void InsertSortedArrayHelper(AvlNode *&root, const vector<Patient> &array, int left, int right)
    {
        if (left > right)
            return;
        if (right == left)
        {
            root = new AvlNode(array[(left + right) / 2], nullptr, nullptr);
            return;
        }
        else
        {
            int middle = (right + left) / 2;

            root = new AvlNode(array[middle], nullptr, nullptr);
            InsertSortedArrayHelper(root->left, array, left, middle - 1); // it's like we have deleted the middle from the list when we are done inserting that node
            InsertSortedArrayHelper(root->right, array, middle + 1, right);
        }
    }
    void storeData(const Patient &patient) const
    {
        FileHandler handler;
        if (is_file_exist("Data/" + patient.getId() + ".txt"))
            handler.InsertMedicalInfo(patient.getMedicalInfo(), patient.getId());
        else
            handler.InsertFullData(patient);
    }
};

#endif