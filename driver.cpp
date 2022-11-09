#include <iostream>
#include <chrono>
#include "Part1/Btree.h"
#include "Part3/AVL.h"
#include "Part2/BST.h"
#include "utilities/FileHandler.h"

using namespace std;

int main()
{ //
  Patient patient("BOUZIGUESSER", "15/13/2023", "AinBessem Tounin Fernaka", 'M', "0770251046", "AB+", MedicalInfo("DiabeteA", "Ghabra", 12.7, 75, {"smecta", "aspirine", "rumafède", "gaviscon"}, "A Stupid Note", 'A'));
  Patient patient2("BLOATWARE", "15/19/2026", "NYC SA7BIII", 'M', "0776992954", "O+", MedicalInfo("Diabete", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "A Stupid Note", 'B'));

  Patient patient3("BLOATWafaARE", "15/19/2026", "NYC SA7BIII", 'M', "0776992954", "A-", MedicalInfo("Diabete3", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "Stupid Note", 'C'));
  Patient patient4("BLOATWafaARE4", "15/19/2026", "NYC SA7BIII", 'M', "0776992954", "A-", MedicalInfo("Diabete3", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "Stupid Note", 'C'));
  Patient patient5("BLOATWafaARE5", "15/19/2026", "NYC SA7BIII", 'M', "0776992954", "A-", MedicalInfo("Chrollo", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "Stupid Note", 'C'));
  Patient patient6("BLOATWafaARE6", "15/19/2026", "NYC SA7BIII", 'M', "0776992954", "A-", MedicalInfo("Chrollo", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "Stupid Note", 'C'));
  FileHandler handler;
  handler.InsertFullData(patient);
  handler.InsertFullData(patient2);
  handler.InsertFullData(patient3);
  handler.InsertFullData(patient4);
  handler.InsertFullData(patient5);
  handler.InsertFullData(patient6);

  vector<Patient> allPatients = handler.getALLPatient();
  AvlTree avl1;
  auto start = chrono::high_resolution_clock::now();
  avl1.InsertSortedArray(allPatients);
  auto end = chrono::high_resolution_clock::now();
  cout << "Duration of the Sorted Array Insertion(AVl): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
  BTree avl2(5);
  auto start2 = chrono::high_resolution_clock::now();
  for (const Patient &p : allPatients)
  {
    avl2.insert(p);
  }
  auto end2 = chrono::high_resolution_clock::now();
  cout << "Duration of the Traditional Way(Btree): " << chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count() << endl;

  start = chrono::high_resolution_clock::now();
  (avl1.contains(patient4.getId()) == true) ? cout << "YEs\n" : cout << "No\n";
  end = chrono::high_resolution_clock::now();
  cout << "Search in Avl: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;

  start = chrono::high_resolution_clock::now();
  (avl1.contains(patient4.getId()) == true) ? cout << "YEs\n" : cout << "No\n";
  end = chrono::high_resolution_clock::now();
  cout << "Search in Btree: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
}
