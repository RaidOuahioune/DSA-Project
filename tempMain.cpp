#include <iostream>
#include "Interfaces/Patient.h"
#include "Interfaces/MedicalInfo.h"
#include "Part2/BST.h"
using namespace std;

int main()
{
    Patient patient("A6516519810", "BOUZIGUESSER", "15/13/2023", "14/13/2023", "AinBessem Tounin Fernaka", 'M', "0776072954", MedicalInfo("AB+", "Diabete", "Ghabra", 12.7, 75, {"smecta", "aspirine", "rumafède", "gaviscon"}));

    Patient patient2("A6511019810", "BLOATWARE", "15/19/2026", "16/13/2027", "NYC SA7BIII", 'M', "0776992954", MedicalInfo("O+", "Diabete", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}));

    Patient patient3("A6991019810", "BLOATWafaARE", "15/19/2026", "16/13/2027", "NYC SA7BIII", 'M', "0776992954", MedicalInfo("O+", "Diabete", "Ghabra", 12.7, 75, {"aspirine", "rumafède", "gaviscon"}));

    /*     patient.printPatient();
     */

    BST bouzi;
    bouzi.InsertElement(patient);
    bouzi.InsertElement(patient2);
    bouzi.InsertElement(patient3);

    bouzi.InOrder();
}