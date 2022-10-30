#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include "MedicalInfo.h"
using std::string;

class Patient
{
public:
    Patient(const string &, const string &, const string &, const string &, const string &, char, const string &, const MedicalInfo &);
    void printPatient() const;
    bool operator<(const Patient &) const;

private:
    string ID;
    string fullName;
    string bDay;      // the birthday is at format dd/MM/yyyy
    string entryDate; // the entry date of the patient at format dd/MM/yyyy
    string adress;
    char FM;        // gender stands for Male or Female
    string tel;     // Phone number in case the hospital needed to concact the patient or the patient's family
    MedicalInfo MI; // from the MedicalInfo class
};

Patient::Patient(const string &ID, const string &fullName, const string &bDay, const string &entryDate, const string &adress, char MF, const string &tel, const MedicalInfo &MI) : ID(ID), fullName(fullName), bDay(bDay), entryDate(entryDate), adress(adress), FM(FM), tel(tel), MI(MI) {}

void Patient::printPatient() const
{
    cout << "ID: " << ID << endl
         << "fullName: " << fullName << endl
         << "Birthday: " << bDay << endl
         << "Entry Date: " << entryDate << endl
         << "Adress: " << adress << endl
         << "Gender: " << ((FM == 'M') ? "Male" : "Female") << endl
         << "Telephone: " << tel << endl;
    MI.printInfo();
}

bool Patient::operator<(const Patient &other) const
{
    string ID1 = other.ID;
    string ID2 = this->ID;

    int sum1(0);
    int sum2(0);
    for (int i = 0; i < ID1.size(); ++i)
    {
        sum1 += ID1[i];
        sum2 += ID2[i];
    }
    return (sum1 < sum2);
};

#endif