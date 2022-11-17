#include <iostream>
#include <unordered_map>
#include "Part1/Btree.h"
#include "Part3/AVL.h"
#include "Part2/BST.h"
#include "utilities/FileHandler.h"
#include "Test/generalTesting.h"
#include "Test/BtreeComparaison.h"
#include <filesystem>
using namespace std;

enum Trees
{
    Bst,
    Avl,
    Btree
};

const Trees Type = Bst;

template <typename TreeType>
TreeType &getTree()
{
    if (Type == Bst)
    {
        static BST TREE;
        TREE.InsertSortedArray(FileHandler().getALLPatient());
        return TREE;
    }
    else if (Type == Avl)
    {
        static AvlTree TREE;
        TREE.InsertSortedArray(FileHandler().getALLPatient());
        return TREE;
    }
    else
    {
        static BTree TREE;
        TREE.InsertSortedArray(FileHandler().getALLPatient());
        return TREE;
    }
}
template <typename TreeType>
void HandleTree(vector<TreeType> &AllTrees)
{
}


int main()
{
    
}