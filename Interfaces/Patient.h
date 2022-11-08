#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <ctime>
#include "MedicalInfo.h"
#include "../utilities/utilities.h"
using std::ostream;
using std::string;

class Patient
{
public:
    Patient(const string &, const string &, const string &, char, const string &, const string &, const MedicalInfo &);
    string getId() const;
    MedicalInfo getMedicalInfo() const;
    void setMedicalInfo(const MedicalInfo &);
    void printPatient() const;
    bool operator<(const Patient &) const;
    bool operator>(const Patient &) const;
    bool operator==(const Patient &) const;

private:
    //{
    string ID;
    string fullName;
    string bDay;      // the birthday is at format dd/MM/yyyy
    string entryDate; // the entry date of the patient at format dd/MM/yyyy
    string adress;
    char FM;    // gender stands for Male or Female
    string tel; // Phone number in case the hospital needed to concact the patient or the patient's family
    string ABO; //  Blood Group System mean Blood Type

    //} // These information are the static information for the patient, (they won't change)

    MedicalInfo MI;         // from the MedicalInfo class
    static int incrementer; // increments everytime a patient is created
    friend class FileHandler;
};

int Patient::incrementer = 10;

Patient::Patient(const string &fullName = "", const string &bDay = "", const string &adress = "", char MF = '\0', const string &tel = "", const string &ABO = "", const MedicalInfo &MI = MedicalInfo()) : fullName(fullName), bDay(bDay), adress(adress), FM(MF), tel(tel), ABO(ABO), MI(MI)
{
    if (++incrementer == 100)
        incrementer = 10;
    srand(time(nullptr));
    ID = generateID(rand()) + std::to_string(incrementer);
    entryDate = getTime();
}

string Patient::getId() const
{
    return this->ID;
}
MedicalInfo Patient::getMedicalInfo() const
{
    return this->MI;
}
void Patient::printPatient() const
{
    cout << "ID: " << ID << endl
         << "FullName: " << fullName << endl
         << "BirthDay: " << bDay << endl
         << "Entry Date: " << entryDate << endl
         << "Adress: " << adress << endl
         << "Gender: " << ((FM == 'M') ? "Male" : "Female") << endl
         << " ABO: " << ABO << endl
         << "Telephone: " << tel << endl;
    MI.printInfo();
}

bool Patient::operator<(const Patient &other) const
{
    return stoll(this->ID) < stoll(other.ID);
};

bool Patient::operator==(const Patient &other) const
{
    return (this->ID == other.ID);
}

bool Patient::operator>(const Patient &other) const
{
    return !((*this) < other) && !((*this) == other);
}

void Patient::setMedicalInfo(const MedicalInfo &info)
{
    this->MI = info;
}

#endif