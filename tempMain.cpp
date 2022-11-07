#include <iostream>
#include "Part3/AVL.h"
#include "utilities/FileHandler.h"

using namespace std;

int main()
{
  Patient patient("6516519810", "BOUZIGUESSER", "15/13/2023", "AinBessem Tounin Fernaka", 'M', "0776072954", MedicalInfo("AB+", "Diabete", "Ghabra", 12.7, 75, {"smecta", "aspirine", "rumafède", "gaviscon"}, "A Stupid Note", 'A'));

  Patient patient2("6511019810", "BLOATWARE", "15/19/2026", "NYC SA7BIII", 'M', "0776992954", MedicalInfo("O+", "Diabete", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "A Stupid Note", 'B'));

  Patient patient3("6991019810", "BLOATWafaARE", "15/19/2026", "NYC SA7BIII", 'M', "0776992954", MedicalInfo("O+", "Diabete", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "Stupid Note", 'C'));

  FileHandler handler;
  // handler.InsertMedicalInfo(patient.getMedicalInfo(),patient.getId());
  handler.InsertFullData(patient);
  vector<MedicalInfo> history = handler.getAllHistory(patient.getId());
  for (const MedicalInfo &info : history)
  {
     info.printInfo();
  }
  handler.InsertMedicalInfo(patient3.getMedicalInfo(),patient.getId());
}
