#ifndef MEDICALINFO_H
#define MEDICALINFO_H

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class MedicalInfo
{
public:
    MedicalInfo(const string &, const string &, const string &, const float &, const float &, const vector<string> &);
    ~MedicalInfo(){};

    void printInfo() const;

private:
    string ABO;                   //  Blood Group System mean Blood Type
    string CD;                    // means if the patient has a chronic disease and what its type
    string Allergies;             // Allergies of the patient
    float BP;                     // Blood Pressure in MMHG(Millimeters Of Mercury unit mesure)
    float HR;                     // Heart Rate in BPS (Beats per Second unit mesure)
    vector<string> MedicalsTaken; // Patient's last taken Medicals

    friend class Patient;
};

MedicalInfo::MedicalInfo(const string &ABO, const string &CD, const string &Allergies, const float &BP, const float &HR, const vector<string> &MedicalsTaken) : ABO(ABO), CD(CD), Allergies(Allergies), BP(BP), HR(HR), MedicalsTaken(MedicalsTaken) {}

void MedicalInfo::printInfo() const
{
    cout << ABO << endl;
    cout << CD << endl;
    cout << Allergies << endl;
    cout << BP << endl;
    cout << HR << endl;
    for (const string &i : MedicalsTaken)
        cout << i << endl;
}

#endif //