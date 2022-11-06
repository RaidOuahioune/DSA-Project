#ifndef MEDICALINFO_H
#define MEDICALINFO_H

#include <iostream>
#include <vector>
#include "../utilities/utilities.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class MedicalInfo
{
public:
    MedicalInfo(const string &, const string &, const string &, const float &, const float &, const vector<string> &, const string &, char);
    ~MedicalInfo(){};

    void printInfo() const;

private:
    string ABO;                   //  Blood Group System mean Blood Type
    string CD;                    // means if the patient has a chronic disease and what its type
    string Allergies;             // Allergies of the patient
    float BP;                     // Blood Pressure in MMHG(Millimeters Of Mercury unit mesure)
    float HR;                     // Heart Rate in BPS (Beats per Second unit mesure)
    vector<string> MedicalsTaken; // Patient's last taken Medicals
    string briefNote;             // in case the doctor needs to leave a comment on patient state
    string time;                  // the time of the diagnosis
    char Department;              // Character representing the department where the information is coming from
    friend class Patient;
    friend class FileHandler;
};

MedicalInfo::MedicalInfo(const string &ABO = "", const string &CD = "", const string &Allergie = "", const float &BP = 0, const float &HR = 0, const vector<string> &MedicalsTaken = {}, const string &note = "", char Department = '\0') : ABO(ABO), CD(CD), Allergies(Allergie), BP(BP), HR(HR), MedicalsTaken(MedicalsTaken), briefNote(note), time(getTime()), Department(Department)
{
}

void MedicalInfo::printInfo() const
{
    cout << ABO << endl;
    cout << CD << endl;
    cout << Allergies << endl;
    cout << BP << endl;
    cout << HR << endl;
    for (const string &i : MedicalsTaken)
        cout << i << endl;
    cout << time << endl;
    cout << Department << endl;
    cout << briefNote << endl;
    cout << endl;
}

#endif //