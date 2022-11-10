#ifndef Test_h
#define Test_h
#include "../utilities/FileHandler.h"
#include "../Part1/Btree.h"
#include "../Part2/BST.h"
#include "../Part3/AVL.h"
namespace Test
{

  void BuildTreeComparaison()
  {
    FileHandler handler;
    vector<Patient> allPatients = handler.getALLPatient();
    AvlTree avl1;
    auto start = chrono::high_resolution_clock::now();
    avl1.InsertSortedArray(allPatients);
    auto end = chrono::high_resolution_clock::now();
    cout << "Duration of the Sorted Array Insertion (AVl): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;

    AvlTree avl2;
    start = chrono::high_resolution_clock::now();
    for (const Patient &p : allPatients)
    {
      avl2.insert(p);
    }
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Traditional Way Build(Avl): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;

    BTree btree(5);
    start = chrono::high_resolution_clock::now();
    for (const Patient &p : allPatients)
    {
      btree.insert(p);
    }
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Traditional Way(Btree): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;

    BST binaryTree;
    start = chrono::high_resolution_clock::now();
    for (const Patient &p : allPatients)
    {
      binaryTree.insert(p);
    }
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Traditional Way(BST): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    BST binaryTree2;
    start = chrono::high_resolution_clock::now();
    binaryTree2.InsertSortedArray(allPatients);
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Sorted Array Insertion (BST): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
  }
}
#endif