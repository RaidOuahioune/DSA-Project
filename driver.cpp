#include <iostream>
#include "Part1/Btree.h"
#include "Part3/AVL.h"
#include "Part2/BST.h"
#include "utilities/FileHandler.h"

using namespace std;

int main()
{
  Patient patient("BOUZIGUESSER", "15/13/2023", "AinBessem Tounin Fernaka", 'M', "0770251046", "AB+", MedicalInfo("DiabeteA", "Ghabra", 12.7, 75, {"smecta", "aspirine", "rumafède", "gaviscon"}, "A Stupid Note", 'A'));
  Patient patient2("BLOATWARE", "15/19/2026", "NYC SA7BIII", 'M', "0776992954", "O+", MedicalInfo("Diabete", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "A Stupid Note", 'B'));

  Patient patient3("BLOATWafaARE", "15/19/2026", "NYC SA7BIII", 'M', "0776992954", "A-", MedicalInfo("Diabete3", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "Stupid Note", 'C'));

  BTree btree(10);
  btree.insert(patient);
  btree.insert(patient2);
  btree.Delete(patient.getId());
  btree.Delete(patient3.getId());
  btree.traverse();

}
