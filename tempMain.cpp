#include <iostream>
#include "Interfaces/Patient.h"
#include "Interfaces/MedicalInfo.h"
#include "utilities/FileHandler.h"

using namespace std;

int main()
{
  Patient patient("A6516519810", "BOUZIGUESSER", "15/13/2023", "14/13/2023", "AinBessem Tounin Fernaka", 'M', "0776072954", MedicalInfo("AB+", "Diabete", "Ghabra", 12.7, 75, {"smecta", "aspirine", "rumafède", "gaviscon"}, "A Stupid Note", 'A'));

  Patient patient2("A6511019810", "BLOATWARE", "15/19/2026", "16/13/2027", "NYC SA7BIII", 'M', "0776992954", MedicalInfo("O+", "Diabete", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "A Stupid Note", 'B'));

  Patient patient3("A6991019810", "BLOATWafaARE", "15/19/2026", "16/13/2027", "NYC SA7BIII", 'M', "0776992954", MedicalInfo("O+", "Diabete", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}, "Stupid Note", 'C'));

  string path = "Data/" + patient.getId().substr(1) + ".txt";
  FileHandler handler(path);
  handler.InsertMedicalInfo(patient.getMedicalInfo());
  vector<MedicalInfo> history = handler.getAllHistory();
  for (const MedicalInfo &info : history)
  {
    info.printInfo();
  }
}
