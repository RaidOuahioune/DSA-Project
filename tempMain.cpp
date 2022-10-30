#include <iostream>
#include "Patient.h"
#include "MedicalInfo.h"
using namespace std;

int main()
{
    Patient patient("A6516519810", "BOUZIGUESSER", "15/13/2023", "14/13/2023", "AinBessem Tounin Fernaka", 'M', "0776072954", MedicalInfo("AB+", "Diabete", "Ghabra", 12.7, 75, {"smecta", "aspirine", "rumafède", "gaviscon"}));

    patient.printPatient();
}