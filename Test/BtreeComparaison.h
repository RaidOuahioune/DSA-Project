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
    ofstream file;
    file.open("Test/BtreeComparaison/BuildTree.csv", std::ios_base::app);

    FileHandler handler;
    vector<Patient> allPatients = handler.getALLPatient();
    file << allPatients.size() << ',';

    for (int y = 0; y < Orders.size(); y++)
    {
      BTree tree(Orders[y]);
      auto start = std::chrono::high_resolution_clock::now();
      for (const Patient &patient : allPatients)
      {
        tree.insert(patient);
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
    ofstream file;
    file.open("Test/BtreeComparaison/Search.csv", std::ios_base::app);
    FileHandler handler;
    vector<Patient> allPatients = handler.getALLPatient();
    srand(time(nullptr));
    int random = rand() % allPatients.size();
    string randomId = allPatients[random].getId();
    file << allPatients.size() << ',';

    for (int y = 0; y < Orders.size(); y++)
    {
      BTree tree(Orders[y]);

      for (const Patient &patient : allPatients)
      {
        tree.insert(patient);
      }
      auto start = std::chrono::high_resolution_clock::now();
      tree.contains(randomId);
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
    fstream file;
    file.open("Test/BtreeComparaison/Insert.csv", ios_base::app);
    FileHandler handler;
    vector<Patient> allPatients = handler.getALLPatient();
    file << allPatients.size() << ',';

    Patient patient = Patient("Raid Ouahioune", "12/10/2004", "Aghouat", 'M', "0669511304", "A+", MedicalInfo("Null", "Null", 12, 10, {}, "Nothing", 'A'));
    for (int y = 0; y < Orders.size(); y++)
    {
      BTree tree(Orders[y]);

      for (const Patient &patient : allPatients)
      {
        tree.insert(patient);
      }
      auto start = std::chrono::high_resolution_clock::now();
      tree.insert(patient);
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
    ofstream file;
    file.open("Test/BtreeComparaison/update.csv", ios_base::app);

    FileHandler handler;
    vector<Patient> allPatients = handler.getALLPatient();
    file << allPatients.size() << ',';

    MedicalInfo info = MedicalInfo("Null", "Null", 12, 10, {}, "Nothing", 'A');

    srand(time(nullptr));
    int random = rand() % allPatients.size();      // to get a random index
    string randomId = allPatients[random].getId(); // get a random ID from the patient at that random position
    for (int y = 0; y < Orders.size(); y++)
    {
      BTree tree(Orders[y]);

      for (const Patient &patient : allPatients)
      {
        tree.insert(patient);
      }
      auto start = std::chrono::high_resolution_clock::now();
      tree.update(randomId, info);
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
    ofstream file;
    file.open("Test/BtreeComparaison/delete.csv", ios_base::app);
    FileHandler handler;
    vector<Patient> allPatients = handler.getALLPatient();
    file << allPatients.size() << ',';

    srand(time(nullptr));
    int random = rand() % allPatients.size();
    string randomId = allPatients[random].getId();

    for (int y = 0; y < Orders.size(); y++)
    {
      BTree tree(Orders[y]);

      for (const Patient &patient : allPatients)
      {
        tree.insert(patient);
      }
      auto start = std::chrono::high_resolution_clock::now();
      tree.Delete(randomId);
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