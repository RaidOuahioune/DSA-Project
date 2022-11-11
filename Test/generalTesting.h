#ifndef Test_h
#define Test_h
#include "../utilities/FileHandler.h"
#include "../Part1/Btree.h"
#include "../Part2/BST.h"
#include "../Part3/AVL.h"
#include <fstream>
using std::fstream;
namespace GeneralTesting
{
  

  void BuildTreeComparaison()
  {
    ofstream file;
    file.open("Test/GenralComparaison/BuildTree.csv", ios_base::app);

    FileHandler handler;
    vector<Patient> allPatients = handler.getALLPatient();
    file << allPatients.size() << ',';

    BST binaryTree;
    auto start = chrono::high_resolution_clock::now();
    for (const Patient &p : allPatients)
    {
      binaryTree.insert(p);
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Duration of the Traditional Way(BST): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';
    BST binaryTree2;
    start = chrono::high_resolution_clock::now();
    binaryTree2.InsertSortedArray(allPatients);
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Sorted Array Insertion (BST): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';
    AvlTree avl1;
    start = chrono::high_resolution_clock::now();
    avl1.InsertSortedArray(allPatients);
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Sorted Array Insertion (AVl): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';
    AvlTree avl2;
    start = chrono::high_resolution_clock::now();
    for (const Patient &p : allPatients)
    {
      avl2.insert(p);
    }
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Traditional Way Build(Avl): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';

    BTree btree(5);
    start = chrono::high_resolution_clock::now();
    for (const Patient &p : allPatients)
    {
      btree.insert(p);
    }
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Traditional Way(Btree): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file.close();
  }

  void SearchComparaison()
  {
    ofstream file;
    file.open("Test/GenralComparaison/Search.csv", ios_base::app);
    FileHandler handler;
    vector<Patient> allPatients = handler.getALLPatient();
    file << allPatients.size() << ',';
    BST BinaryTree;
    AvlTree avlTree;
    BTree btree(5);
    BinaryTree.InsertSortedArray(allPatients);
    avlTree.InsertSortedArray(allPatients);
    for (const Patient &patient : allPatients)
    {
      btree.insert(patient);
    }

    srand(time(nullptr));
    int random = rand() % allPatients.size();
    string randomId = allPatients[random].getId();

    auto start = chrono::high_resolution_clock::now();
    BinaryTree.contains(randomId);
    auto end = chrono::high_resolution_clock::now();
    cout << "Duration  of seaching in A BST : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';

    start = chrono::high_resolution_clock::now();
    avlTree.contains(randomId);
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the seaching  in An AvlTree : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';
    start = chrono::high_resolution_clock::now();
    btree.contains(randomId);
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the seaching  in Btree with order 10 : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file.close();
  }

  void InsertionComparaison()
  {
    fstream file;
    file.open("Test/GenralComparaison/Insert.csv", ios_base::app);
    FileHandler handler;
    vector<Patient> allPatients = handler.getALLPatient();
    file << allPatients.size() << ',';
    BST BinaryTree;
    AvlTree avlTree;
    BTree btree(5);
    BinaryTree.InsertSortedArray(allPatients);
    avlTree.InsertSortedArray(allPatients);
    for (const Patient &patient : allPatients)
    {
      btree.insert(patient);
    }
    Patient patient = Patient("Raid Ouahioune", "12/10/2004", "Aghouat", 'M', "0669511304", "A+", MedicalInfo("Null", "Null", 12, 10, {}, "Nothing", 'A'));

    auto start = chrono::high_resolution_clock::now();
    BinaryTree.insert(patient);
    auto end = chrono::high_resolution_clock::now();
    cout << "Duration of inserting in A BST : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';
    start = chrono::high_resolution_clock::now();
    avlTree.insert(patient);
    end = chrono::high_resolution_clock::now();
    cout << "Duration of inserting  in An AvlTree : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';

    start = chrono::high_resolution_clock::now();
    btree.insert(patient);
    end = chrono::high_resolution_clock::now();
    cout << "Duration of inserting in Btree with order 10 : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;

    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file.close();
  }

  void UpdateComparaison()
  {
    ofstream file;
    file.open("Test/GenralComparaison/update.csv", ios_base::app);

    FileHandler handler;
    vector<Patient> allPatients = handler.getALLPatient();
    file << allPatients.size() << ',';
    BST BinaryTree;
    AvlTree avlTree;
    BTree btree(5);
    BinaryTree.InsertSortedArray(allPatients);
    avlTree.InsertSortedArray(allPatients);
    for (const Patient &patient : allPatients)
    {
      btree.insert(patient);
    }

    MedicalInfo info = MedicalInfo("Null", "Null", 12, 10, {}, "Nothing", 'A');

    srand(time(nullptr));
    int random = rand() % allPatients.size();      // to get a random index
    string randomId = allPatients[random].getId(); // get a random ID from the patient at that random position

    auto start = chrono::high_resolution_clock::now();
    BinaryTree.update(randomId, info);
    auto end = chrono::high_resolution_clock::now();
    cout << "Duration of Update in A BST : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';

    start = chrono::high_resolution_clock::now();
    avlTree.update(randomId, info);
    end = chrono::high_resolution_clock::now();
    cout << "Duration of Update in An AvlTree : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';
    start = chrono::high_resolution_clock::now();
    btree.update(randomId, info);
    end = chrono::high_resolution_clock::now();
    cout << "Duration of Update in Btree with order 10 : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file.close();
  }

  void DeleteComparaison()
  {
    ofstream file;
    file.open("Test/GenralComparaison/delete.csv", ios_base::app);
    FileHandler handler;
    vector<Patient> allPatients = handler.getALLPatient();
    file << allPatients.size() << ',';
    BST BinaryTree;
    AvlTree avlTree;
    BTree btree(5);
    BinaryTree.InsertSortedArray(allPatients);
    avlTree.InsertSortedArray(allPatients);
    for (const Patient &patient : allPatients)
    {
      btree.insert(patient);
    }

    srand(time(nullptr));
    int random = rand() % allPatients.size();
    string randomId = allPatients[random].getId();

    auto start = chrono::high_resolution_clock::now();
    BinaryTree.Delete(randomId);
    auto end = chrono::high_resolution_clock::now();
    cout << "Duration  of Deleting in A BST : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';

    start = chrono::high_resolution_clock::now();
    avlTree.Delete(randomId);
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Deleting  in An AvlTree : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';

    start = chrono::high_resolution_clock::now();
    btree.Delete(randomId);
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Deleting  in Btree with order 10 : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file.close();
  }

  void addNewPatients()
  {
    FileHandler handler;
    for (int y = 1; y <= 10; y++)
    {
      Patient patient;
      handler.InsertFullData(patient);
    }
  }

  void GenerateData()
  {
    for (int y = 1; y <= 300; y++)
    {
      BuildTreeComparaison();
      SearchComparaison();
      InsertionComparaison();
      UpdateComparaison();
      DeleteComparaison();
      addNewPatients();
    }
  }

  

}
#endif