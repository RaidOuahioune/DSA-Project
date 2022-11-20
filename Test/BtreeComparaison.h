#ifndef BtreeComparaison_h
#define BtreeComparaison_h
#include <fstream>
#include <chrono>
#include "../utilities/FileHandler.h"
#include "../Part1/Btree.h"

using namespace std;
namespace BtreeComparaison
{

  vector<int> Orders = {2, 3, 4, 5, 6};
  void BuildTreeComparaison()
  {
    int size = 0;
    ofstream file;
    file.open("Test/BtreeComparaison/BuildTree.csv", std::ios_base::app);

    FileHandler handler;
    vector<vector<Patient>> allPatients = handler.getALLPatient(size);
    file << size << ',';

    for (int y = 0; y < Orders.size(); y++)
    {
      vector<BTree> Btrees(NUMBER_OF_DEPARTMENTS);
      for (BTree &tree : Btrees)
      {
        tree = BTree(Orders[y]);
      }

      auto start = std::chrono::high_resolution_clock::now();
      for (const vector<Patient> &vec : allPatients)
      {

        for (const Patient &patient : vec)
        {
          Btrees[patient.getDepartment() - 'A'].insert((patient));
        }
      }
      auto end = std::chrono::high_resolution_clock::now();
      file << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
      if (Orders[y] != 6)
        file << ',';
    }
    file << endl;

    file.close();
  }

  void SearchComparaison()
  {
    int size = 0;
    ofstream file;
    file.open("Test/BtreeComparaison/Search.csv", std::ios_base::app);
    FileHandler handler;
    vector<vector<Patient>> allPatients = handler.getALLPatient(size);
    srand(time(nullptr));

    int randomDep = 0;
    while (allPatients[randomDep].size() == 0)
    {
      randomDep = rand() % NUMBER_OF_DEPARTMENTS;
    }
    int random = rand() % allPatients[randomDep].size();
    string randomId = allPatients[randomDep][random].getId();
    file << size << ',';

    for (int y = 0; y < Orders.size(); y++)
    {
      vector<BTree> Btrees(NUMBER_OF_DEPARTMENTS);
      for (BTree &tree : Btrees)
      {
        tree = BTree(Orders[y]);
      }

      for (const vector<Patient> &vec : allPatients)
      {

        for (const Patient &patient : vec)
        {
          Btrees[patient.getDepartment() - 'A'].insert((patient));
        }
      }
      auto start = std::chrono::high_resolution_clock::now();
      Btrees[randomDep].contains(randomId);
      auto end = std::chrono::high_resolution_clock::now();
      file << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
      if (Orders[y] != 6)
        file << ',';
    }
    file << endl;

    file.close();
  }

  void InsertionComparaison()
  {
    int size = 0;
    fstream file;
    file.open("Test/BtreeComparaison/Insert.csv", ios_base::app);
    FileHandler handler;
    vector<vector<Patient>> allPatients = handler.getALLPatient(size);
    file << size << ',';

    Patient patient = Patient("Raid Ouahioune", "12/10/2004", "Aghouat", 'M', "0669511304", "A+", MedicalInfo("Null", "Null", 12, 10, {}, "Nothing", 'A'));
    for (int y = 0; y < Orders.size(); y++)
    {
      vector<BTree> Btrees(NUMBER_OF_DEPARTMENTS);
      for (BTree &tree : Btrees)
      {
        tree = BTree(Orders[y]);
      }

      for (const vector<Patient> &vec : allPatients)
      {

        for (const Patient &patient : vec)
        {
          Btrees[patient.getDepartment() - 'A'].insert((patient));
        }
      }
      int randomDep = 0;
      while (allPatients[randomDep].size() == 0)
      {
        randomDep = rand() % NUMBER_OF_DEPARTMENTS;
      }

      auto start = std::chrono::high_resolution_clock::now();
      Btrees[randomDep].insert(patient);
      auto end = std::chrono::high_resolution_clock::now();
      file << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
      if (Orders[y] != 6)
        file << ',';
    }
    file << endl;
    file.close();
  }

  void UpdateComparaison()
  {
    int size = 0;
    ofstream file;
    file.open("Test/BtreeComparaison/update.csv", ios_base::app);

    FileHandler handler;
    vector<vector<Patient>> allPatients = handler.getALLPatient(size);
    file << size << ',';

    MedicalInfo info = MedicalInfo("Null", "Null", 12, 10, {}, "Nothing", 'A');

    srand(time(nullptr));

    int randomDep = 0;
    while (allPatients[randomDep].size() == 0)
    {
      randomDep = rand() % NUMBER_OF_DEPARTMENTS;
    }
    int random = rand() % allPatients[randomDep].size();
    // to get a random index
    string randomId = allPatients[randomDep][random].getId(); // get a random ID from the patient at that random position
    for (int y = 0; y < Orders.size(); y++)
    {
      vector<BTree> Btrees(NUMBER_OF_DEPARTMENTS);
      for (BTree &tree : Btrees)
      {
        tree = BTree(Orders[y]);
      }

      for (const vector<Patient> &vec : allPatients)
      {

        for (const Patient &patient : vec)
        {
          Btrees[patient.getDepartment() - 'A'].insert((patient));
        }
      }
      auto start = std::chrono::high_resolution_clock::now();
      Btrees[randomDep].update(randomId, info);
      auto end = std::chrono::high_resolution_clock::now();
      file << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
      if (Orders[y] != 6)
        file << ',';
    }
    file << endl;

    file.close();
  }

  void DeleteComparaison()
  {
    int size = 0;
    ofstream file;
    file.open("Test/BtreeComparaison/delete.csv", ios_base::app);
    FileHandler handler;
    vector<vector<Patient>> allPatients = handler.getALLPatient(size);
    file << size << ',';

    srand(time(nullptr));

    int randomDep = 0;
    while (allPatients[randomDep].size() == 0)
    {
      randomDep = rand() % NUMBER_OF_DEPARTMENTS;
    }
    int random = rand() % allPatients[randomDep].size();
    string randomId = allPatients[randomDep][random].getId();

    for (int y = 0; y < Orders.size(); y++)
    {
      vector<BTree> Btrees(NUMBER_OF_DEPARTMENTS);
      bool dummy = true;
      for (BTree &tree : Btrees)
      {
        tree = BTree(Orders[y]);
      }

      for (const vector<Patient> &vec : allPatients)
      {

        for (const Patient &patient : vec)
        {
          Btrees[patient.getDepartment() - 'A'].insert((patient));
        }
      }
      auto start = std::chrono::high_resolution_clock::now();
      Btrees[randomDep].Delete(randomId, dummy);
      auto end = std::chrono::high_resolution_clock::now();
      file << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
      if (Orders[y] != 6)
        file << ',';
    }
    file << endl;

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
      addNewPatients();
      BuildTreeComparaison();
      SearchComparaison();
      InsertionComparaison();
      UpdateComparaison();
      DeleteComparaison();
    }
  }

}

#endif