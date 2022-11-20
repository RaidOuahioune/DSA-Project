// Leader Full Name: Ouahioune Raid Abderrezak

// Group:4

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
    MedicalInfo(const string &, const string &, const float &, const float &, const vector<string> &, const string &, char);
    ~MedicalInfo()
    {
    }
    void setCd(const string &);
    void setAllergies(const string &);
    void setBP(float);
    void setHr(float);
    void setMedicalstaken(const vector<string> &);
    void setNote(const string &);
    void setTime(const string &);
    void setDepartment(const char &);
    void printInfo() const;

private:
    string CD;                    // means if the patient has a chronic disease and what its type
    string Allergies;             // Allergies of the patient
    float BP;                     // Blood Pressure in MMHG(Millimeters Of Mercury unit mesure)
    float HR;                     // Heart Rate in BPS (Beats per Minte unit mesure)
    vector<string> MedicalsTaken; // Patient's last taken Medicals
    string briefNote;             // in case the doctor needs to leave a comment on patient state
    string time;                  // the time of the diagnosis
    char Department;              // Character representing the department where the information is coming from
    friend class Patient;
    friend class FileHandler;
};

MedicalInfo::MedicalInfo(const string &CD = generateCDS(), const string &Allergie = generateAllergies(), const float &BP = generateBP(), const float &HR = generateHB(), const vector<string> &MedicalsTaken = generateMedicals(), const string &note = "", char Department = char(65 + rand() % 5)) : CD(CD), Allergies(Allergie), BP(BP), HR(HR), MedicalsTaken(MedicalsTaken), briefNote(note), Department(Department)
{
    time = getTime();
}

void MedicalInfo::setCd(const string &a)
{
    this->CD = a;
}
void MedicalInfo::setAllergies(const string &a)
{
    this->Allergies = a;
}
void MedicalInfo::setBP(float a)
{
    if (a >= 0)
        this->BP = a;
}
void MedicalInfo::setHr(float a)
{
    if (a >= 0)
        this->HR = a;
}
void MedicalInfo::setMedicalstaken(const vector<string> &array)
{
    this->MedicalsTaken = array;
}
void MedicalInfo::setNote(const string &a)
{
    this->briefNote = a;
}

void MedicalInfo::setTime(const string &time)
{
    this->time = time;
}

void MedicalInfo::setDepartment(const char &a)
{
    if (a == 'A' || a == 'B' || a == 'C' || a == 'D' || a == 'E' || a == 'N')
        this->Department = a;
}

void MedicalInfo::printInfo() const
{
    cout << "Chronical Diseases: " << CD << endl;
    cout << "Allergies: " << Allergies << endl;
    cout << "Blood Pressure: " << BP << endl;
    cout << "Heart Rate: " << HR << endl;
    cout << "MedicalsTaken: ";
    for (const string &i : MedicalsTaken)
        cout << i << " ";
    cout << endl;
    cout << "time: " << time << endl;
    cout << "Department: " << Department << endl;
    cout << "briefNote:" << briefNote << endl;
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
}
#endif //