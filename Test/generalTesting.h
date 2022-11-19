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
    int size = 0;
    ofstream file;
    file.open("Test/GenralComparaison/BuildTree.csv", ios_base::app);

    FileHandler handler;
    vector<vector<Patient>> allPatients = handler.getALLPatient(size);
    file << size << ',';

    vector<BST> BSTtrees(NUMBER_OF_DEPARTMENTS);
    auto start = chrono::high_resolution_clock::now();
    for (const vector<Patient> &vec : allPatients)
    {

      for (const Patient &patient : vec)
      {
        BSTtrees[patient.getDepartment() - 'A'].insert((patient));
      }
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Duration of the Traditional Way(BST): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';
    vector<BST> BSTtrees2(NUMBER_OF_DEPARTMENTS);
    start = chrono::high_resolution_clock::now();
    for (int y = 0; y < NUMBER_OF_DEPARTMENTS; y++)
    {
      BSTtrees2[y].InsertSortedArray(allPatients[y]);
    }
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Sorted Array Insertion (BST): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';
    vector<AvlTree> AVltrees(NUMBER_OF_DEPARTMENTS);
    start = chrono::high_resolution_clock::now();
    for (int y = 0; y < NUMBER_OF_DEPARTMENTS; y++)
    {
      AVltrees[y].InsertSortedArray(allPatients[y]);
    }
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Sorted Array Insertion (AVl): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';
    vector<AvlTree> AVltrees2(NUMBER_OF_DEPARTMENTS);
    start = chrono::high_resolution_clock::now();
    for (const vector<Patient> &vec : allPatients)
    {

      for (const Patient &patient : vec)
      {
        AVltrees2[patient.getDepartment() - 'A'].insert((patient));
      }
    }
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Traditional Way Build(Avl): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';

    vector<BTree> Btrees(NUMBER_OF_DEPARTMENTS);
    for (BTree &tree : Btrees)
    {
      tree = BTree(NUMBER_OF_DEPARTMENTS);
    }

    start = std::chrono::high_resolution_clock::now();
    for (const vector<Patient> &vec : allPatients)
    {

      for (const Patient &patient : vec)
      {
        Btrees[patient.getDepartment() - 'A'].insert((patient));
      }
    }

    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Traditional Way(Btree): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';

    vector<BTree> btrees2(NUMBER_OF_DEPARTMENTS);
    start = chrono::high_resolution_clock::now();
    for (int y = 0; y < NUMBER_OF_DEPARTMENTS; y++)
    {
      btrees2[y].InsertSortedArray(allPatients[y]);
    }
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Sorted Array Insertion (Btree): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;

    file.close();
  }

  void SearchComparaison()
  {
    int size = 0;
    ofstream file;
    file.open("Test/GenralComparaison/Search.csv", ios_base::app);
    FileHandler handler;
    vector<vector<Patient>> allPatients = handler.getALLPatient(size);
    file << size << ',';
    vector<BST> BSTtrees(NUMBER_OF_DEPARTMENTS);
    vector<AvlTree> AVltrees(NUMBER_OF_DEPARTMENTS);
    vector<BTree> Btrees(NUMBER_OF_DEPARTMENTS);
    for (BTree &tree : Btrees)
    {
      tree = BTree(NUMBER_OF_DEPARTMENTS);
    }

    for (const vector<Patient> &vec : allPatients)
    {

      for (const Patient &patient : vec)
      {
        Btrees[patient.getDepartment() - 'A'].insert(patient);
      }
    }

    srand(time(nullptr));

    int randomDep = 0;
    while (allPatients[randomDep].size() == 0)
    {
      randomDep = rand() % NUMBER_OF_DEPARTMENTS;
    }
    int random = rand() % allPatients[randomDep].size();
    string randomId = allPatients[randomDep][random].getId();

    auto start = chrono::high_resolution_clock::now();
    BSTtrees[randomDep].contains(randomId);
    auto end = chrono::high_resolution_clock::now();
    cout << "Duration  of Searching in A BST : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';

    start = chrono::high_resolution_clock::now();
    AVltrees[randomDep].contains(randomId);
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Searching  in An AvlTree : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';
    start = chrono::high_resolution_clock::now();
    BSTtrees[randomDep].contains((randomId));
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Searching  in Btree with order 10 : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file.close();
  }

  void InsertionComparaison()
  {
    int size = 0;
    Patient patient = Patient("Raid Ouahioune", "12/10/2004", "Aghouat", 'M', "0669511304", "A+", MedicalInfo("Null", "Null", 12, 10, {}, "Nothing", 'A'));
    ofstream file;
    file.open("Test/GenralComparaison/Insert.csv", ios_base::app);
    FileHandler handler;
    vector<vector<Patient>> allPatients = handler.getALLPatient(size);
    file << size << ',';
    vector<BST> BSTtrees(NUMBER_OF_DEPARTMENTS);
    vector<AvlTree> AVltrees(NUMBER_OF_DEPARTMENTS);
    vector<BTree> Btrees(NUMBER_OF_DEPARTMENTS);
    for (BTree &tree : Btrees)
    {
      tree = BTree(NUMBER_OF_DEPARTMENTS);
    }

    for (const vector<Patient> &vec : allPatients)
    {

      for (const Patient &patient : vec)
      {
        Btrees[patient.getDepartment() - 'A'].insert((patient));
      }
    }

    srand(time(nullptr));

    int randomDep = 0;
    while (allPatients[randomDep].size() == 0)
    {
      randomDep = rand() % NUMBER_OF_DEPARTMENTS;
    }
    auto start = chrono::high_resolution_clock::now();
    BSTtrees[randomDep].insert(patient);
    auto end = chrono::high_resolution_clock::now();
    cout << "Duration  of Inserting in A BST : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';

    start = chrono::high_resolution_clock::now();
    AVltrees[randomDep].insert(patient);
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Inserting  in An AvlTree : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';
    start = chrono::high_resolution_clock::now();
    BSTtrees[randomDep].insert((patient));
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the Inserting  in Btree with order 10 : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file.close();
  }

  void UpdateComparaison()
  {
    int size = 0;

    MedicalInfo info = MedicalInfo("Null", "Null", 12, 10, {}, "Nothing", 'A');

    ofstream file;
    file.open("Test/GenralComparaison/update.csv", ios_base::app);
    FileHandler handler;
    vector<vector<Patient>> allPatients = handler.getALLPatient(size);
    file << size << ',';
    vector<BST> BSTtrees(NUMBER_OF_DEPARTMENTS);
    vector<AvlTree> AVltrees(NUMBER_OF_DEPARTMENTS);
    vector<BTree> Btrees(NUMBER_OF_DEPARTMENTS);
    for (BTree &tree : Btrees)
    {
      tree = BTree(NUMBER_OF_DEPARTMENTS);
    }

    for (const vector<Patient> &vec : allPatients)
    {

      for (const Patient &patient : vec)
      {
        Btrees[patient.getDepartment() - 'A'].insert((patient));
      }
    }

    srand(time(nullptr));

    int randomDep = 0;
    while (allPatients[randomDep].size() == 0)
    {
      randomDep = rand() % NUMBER_OF_DEPARTMENTS;
    }
    int random = rand() % allPatients[randomDep].size();
    string randomId = allPatients[randomDep][random].getId();

    auto start = chrono::high_resolution_clock::now();
    BSTtrees[randomDep].update(randomId, info);
    auto end = chrono::high_resolution_clock::now();
    cout << "Duration  of update in A BST : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';

    start = chrono::high_resolution_clock::now();
    AVltrees[randomDep].update(randomId, info);
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the update  in An AvlTree : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';
    start = chrono::high_resolution_clock::now();
    BSTtrees[randomDep].update(randomId, info);
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the update  in Btree with order 10 : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file.close();
  }

  void DeleteComparaison()
  {
    int size = 0;
    ofstream file;
    file.open("Test/GenralComparaison/delete.csv", ios_base::app);
    FileHandler handler;
    vector<vector<Patient>> allPatients = handler.getALLPatient(size);
    file << size << ',';
    vector<BST> BSTtrees(NUMBER_OF_DEPARTMENTS);
    vector<AvlTree> AVltrees(NUMBER_OF_DEPARTMENTS);
    vector<BTree> Btrees(NUMBER_OF_DEPARTMENTS);
    for (BTree &tree : Btrees)
    {
      tree = BTree(NUMBER_OF_DEPARTMENTS);
    }

    for (const vector<Patient> &vec : allPatients)
    {

      for (const Patient &patient : vec)
      {
        Btrees[patient.getDepartment() - 'A'].insert((patient));
      }
    }

    srand(time(nullptr));

    int randomDep = 0;
    while (allPatients[randomDep].size() == 0)
    {
      randomDep = rand() % NUMBER_OF_DEPARTMENTS;
    }
    int random = rand() % allPatients[randomDep].size();
    string randomId = allPatients[randomDep][random].getId();

    auto start = chrono::high_resolution_clock::now();
    BSTtrees[randomDep].Delete((randomId));
    auto end = chrono::high_resolution_clock::now();
    cout << "Duration  of delete in A BST : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';

    start = chrono::high_resolution_clock::now();
    AVltrees[randomDep].Delete((randomId));
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the delete  in An AvlTree : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    file << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << ',';
    start = chrono::high_resolution_clock::now();
    BSTtrees[randomDep].Delete((randomId));
    end = chrono::high_resolution_clock::now();
    cout << "Duration of the delete  in Btree with order 10 : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
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

  void GenerateDataAndTest()
  {
    for (int y = 1; y <= 10; y++)
    {
      addNewPatients();
      BuildTreeComparaison();
      SearchComparaison();
      InsertionComparaison();
      UpdateComparaison();
      DeleteComparaison();
    }
  }
  void GenerateDataOnly()
  {
    for (int y = 1; y < 100000; y++)
    {
      addNewPatients();
    }
  }

}
#endif