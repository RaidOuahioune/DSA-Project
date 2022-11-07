#include <iostream>
#include "Part3/AVL.h"
#include "utilities/FileHandler.h"

using namespace std;

int main()
{
  Patient patient("6516519810", "BOUZIGUESSER", "15/13/2023", "AinBessem Tounin Fernaka", 'M', "0776072954", "AB+", MedicalInfo("DiabeteA", "Ghabra", 12.7, 75, {"smecta", "aspirine", "rumafède", "gaviscon"}, "A Stupid Note", 'A'));

  Patient patient2("6511019810", "BLOATWARE", "15/19/2026", "NYC SA7BIII", 'M', "0776992954", "O+", MedicalInfo("Diabete", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "A Stupid Note", 'B'));

  Patient patient3("6991019810", "BLOATWafaARE", "15/19/2026", "NYC SA7BIII", 'M', "0776992954", "A-", MedicalInfo("Diabete3", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "Stupid Note", 'C'));

  AvlTree avl;
  
  avl.insert(patient);
  avl.update(patient.getId(), patient3.getMedicalInfo());
  avl.insert(patient);
  avl.insert(patient2);
  avl.insert(patient3);
  avl.printTree();
  

}
