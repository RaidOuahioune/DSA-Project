#ifndef FUNCTIONALITIES_H
#define FUNCTIONALITIES_H

#include <iostream>
#include "Part1/Btree.h"
#include "Part2/BST.h"
#include "Part3/AVL.h"
#include "Interfaces/Hospital.h"
#include "Interfaces/MedicalInfo.h"
#include "Interfaces/Patient.h"

using namespace std;

namespace DriverFunctions
{
    MedicalInfo EnterMedicalinfos()
    {
        MedicalInfo medicalInfo;

        string Allergeies, CD, Note;
        float BP, HR;
        char Depart;
        vector<string> MedicalTaken;

        cout << "Enter a Chronic Disease of the Patient if available\t";
        cin >> CD;
        cout << "Enter the Allergies of the Patient\t";
        getline(cin, Allergeies);
        cout << "Enter the current Blood Pressure of the Patient: ";
        cin >> BP;
        cout << "Enter the Heart Rate in BPS of the Patient: ";
        cin >> HR;
        cout << "Enter the Department of the Patient\t";
        cin >> Depart;

        cout << "Enter the Medicals taken by the Patient (-1) to quit";
        string medical;
        while (true)
        {
            cin >> medical;
            if (medical == "-1")
                break;
            MedicalTaken.push_back(medical);
        }

        cout << "Enter an Addtional Note: ";
        getline(cin, Note);

        medicalInfo.setAllergies(Allergeies);
        medicalInfo.setCd(CD);
        medicalInfo.setDepartment(Depart);
        medicalInfo.setMedicalstaken(MedicalTaken);
        medicalInfo.setBP(BP);
        medicalInfo.setHr(HR);
        medicalInfo.setNote(Note);
        medicalInfo.setTime(getTime());

        return medicalInfo;
    }

    Patient enterPatient()
    {

        Patient patient;

        string fullName, bDay, entryDate, adress, tel, ABO;
        char FM;

        cout << "Enter the name of the patient : ";
        getline(cin, fullName);
        cout << "Enter the Adress of the patient : ";
        getline(cin, adress);
        cout << "Enter the Birth Date of the patient \" dd/mm/yyyy \" : ";
        cin >> bDay;
        cout << "Enter the gender of the patient ( M for male & F for female) : ";
        cin >> FM;
        cout << "Enter the blood type of the patient : ";
        cin >> ABO;
        cout << "Enter the phone number of the patient : ";
        cin >> tel;
        cout << "Today's date : \" dd/mm/yyyy \": ";
        cin >> entryDate;

        MedicalInfo info = EnterMedicalinfos();

        patient.setAbo(ABO);
        patient.setAddress(adress);
        patient.setBday(bDay);
        patient.setFm(FM);
        patient.setMedicalInfo(info);
        patient.setName(fullName);
        patient.setPhone(tel);

        return patient;
    }

    void DoctorInput()
    {
        // The Developer has the right to edit the ADT used in the hospital.
        Hospital<BST> Hospital;

        char a;
        cout << "Dear Doctor, Please Pick An Option Among The Following Ones, Concerning the Hospital: (Enter The Character That is corresponding to the desired option) \n"
             << "a) Add A Patient\n"
             << "u) Update The Information Of an Existing Patient\n"
             << "r) Remove A Patient\n"
             << "s) Search For a Patient (Check if a Patient already exists)\n"
             << "l) Patient is leaving Hospital\n"
             << "p) Display Patient\n"
             << "q) Quit The Program\n";
        while (true)
        {
            cin >> a;
            switch (a)
            {
            case 'a':
            {
                Patient patient = enterPatient();
                Hospital.insert(patient);
                break;
            }
            case 'u':
            {
                string ID;
                cout << "Enter the ID of the Existing Patient ";
                cin >> ID;
                MedicalInfo medInfo = EnterMedicalinfos();
                Hospital.update(ID, medInfo);
                break;
            }
            case 'r':
            {
                string ID;
                cout << "Enter the ID of the Existing Patient Desired to be Removed";
                cin >> ID;
                Hospital.deletePatient(ID);
                break;
            }
            case 's':
            {
                string ID;
                cout << "Enter the ID of the Existing Patient Desired to be Removed";
                cin >> ID;
                cout << (Hospital.contains(ID) ? "Patient already exists" : "Patient does not exists");
                break;
            }
            case 'l':
            {
                string ID;
                cout << "Enter the ID of the Existing Patient Desired to be Removed";
                cin >> ID;
                Hospital.LeaveHospital(ID);
                break;
            }
            case 'p':
            {
                string ID;
                cout << "Enter the ID of the Existing Patient Desired to be Removed";
                cin >> ID;
                Hospital.printPatient(ID);
                break;
            }
            case 'q':
            {
                return;
            }
            }
        }
    }

}

#endif