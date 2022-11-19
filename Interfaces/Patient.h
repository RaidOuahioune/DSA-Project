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
    bool operator<(const Patient &) const;
    bool operator>(const Patient &) const;
    bool operator==(const Patient &) const;
    string getId() const;
    MedicalInfo getMedicalInfo() const;
    void setMedicalInfo(const MedicalInfo &);
    void printPatient() const;
    char getDepartment() const;
    void setName(const string &);
    void setBday(const string &);
    void setAddress(const string &);
    void setFm(const char &);
    void setPhone(const string &);
    void setAbo(const string &);

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

Patient::Patient(const string &fullName = generateFUllName(), const string &bDay = generateBDay(), const string &adress = generateAdress(), char MF = generateFM(), const string &tel = generateTel(), const string &ABO = generateABO(), const MedicalInfo &MI = MedicalInfo()) : fullName(fullName), bDay(bDay), adress(adress), FM(MF), tel(tel), ABO(ABO), MI(MI)
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
         << "ABO: " << ABO << endl
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

char Patient::getDepartment() const
{
    return this->MI.Department;
}
void Patient::setName(const string &a)
{
    this->fullName = a;
}
void Patient::setBday(const string &a)
{
    this->bDay = a;
}

void Patient::setAddress(const string &a)
{
    this->adress = a;
}
void Patient ::setFm(const char &a)
{
    if (a == 'M' || a == 'F' || a == 'U')
        this->FM = a;
}
void Patient ::setPhone(const string &a)
{
    this->tel = a;
}
void Patient ::setAbo(const string &a)
{
    this->ABO = a;
}
void Patient::setMedicalInfo(const MedicalInfo &info)
{
    this->MI = info;
}

#endif