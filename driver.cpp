#include <iostream>
#include "Part3/AVL.h"
#include "Part2/BST.h"
#include "utilities/FileHandler.h"

using namespace std;

int main()
{
  Patient patient("BOUZIGUESSER", "15/13/2023", "AinBessem Tounin Fernaka", 'M', "0770251046", "AB+", MedicalInfo("DiabeteA", "Ghabra", 12.7, 75, {"smecta", "aspirine", "rumafède", "gaviscon"}, "A Stupid Note", 'A')); /*
   int a = 0;
   for (int i = 0; i < 1000000; ++i)
     a++; */
  Patient patient2("BLOATWARE", "15/19/2026", "NYC SA7BIII", 'M', "0776992954", "O+", MedicalInfo("Diabete", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "A Stupid Note", 'B'));

  Patient patient3("BLOATWafaARE", "15/19/2026", "NYC SA7BIII", 'M', "0776992954", "A-", MedicalInfo("Diabete3", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "Stupid Note", 'C'));

  cout << patient.getId() << endl;
  cout << patient2.getId() << endl;
  cout << patient3.getId() << endl;

  /* BST tree;
  tree.insert(patient);
  tree.insert(patient2);
  tree.update(patient.getId(), patient3.getMedicalInfo());
  // tree.InOrder();
  cout << tree.getNumberOfPatient(); */
}
