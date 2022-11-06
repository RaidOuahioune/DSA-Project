#include <iostream>
#include "Part3/AVL.h"

using namespace std;

int main()
{
  Patient patient("6516519810", "BOUZIGUESSER", "15/13/2023", "14/13/2023", "AinBessem Tounin Fernaka", 'M', "0776072954", MedicalInfo("AB+", "Diabete", "Ghabra", 12.7, 75, {"smecta", "aspirine", "rumafède", "gaviscon"}, "A Stupid Note", 'A'));

  Patient patient2("6511019810", "BLOATWARE", "15/19/2026", "16/13/2027", "NYC SA7BIII", 'M', "0776992954", MedicalInfo("O+", "Diabete", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "A Stupid Note", 'B'));

  Patient patient3("6991019810", "BLOATWafaARE", "15/19/2026", "16/13/2027", "NYC SA7BIII", 'M', "0776992954", MedicalInfo("O+", "Diabete", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "Stupid Note", 'C'));
  AvlTree tree;
  tree.insert(patient);
  tree.insert(patient2);
  tree.insert(patient3);
  cout << tree.contains("6516519810");
}
