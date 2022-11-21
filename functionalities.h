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
    bool checkId(const string &ID)
    {
        try
        {
            stoll(ID);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }
    MedicalInfo EnterMedicalinfos()
    {
        MedicalInfo medicalInfo;

        string Allergeies, CD, Note;
        float BP(0), HR(0);
        char Depart;
        vector<string> MedicalTaken;

        cout << "Enter Depart Chronic Disease of the Patient if available: ";
        getline(cin >> ws, CD);
        cout << "Enter the Allergies of the Patient: ";
        getline(cin >> ws, Allergeies);
        bool notDigit = true;
        do
        {
            string text;
            cout << "Enter the current Blood Pressure of the Patient: ";
            cin >> text;
            try
            {
                BP = stof(text);
                notDigit = false;
            }
            catch (...)
            {
                cout << "Please enter the Blood Pressure as A Number !" << endl;
            }

        } while (notDigit);
        notDigit = true;
        do
        {
            string text;

            cout
                << "Enter the current Heart Rate of the Patient: ";
            cin >> text;
            try
            {

                BP = stof(text);
                notDigit = false;
            }
            catch (...)
            {

                cout
                    << "Please enter the Heart Rate  as A Number !" << endl;
            }

        } while (notDigit);
        do
        {
            cout << "Enter the Department of the Patient:(A OR B OR C OR D OR E( where E Is the critical Unit department)) :";

            cin >> Depart;
        } while (!(Depart == 'A' || Depart == 'B' || Depart == 'C' || Depart == 'D' || Depart == 'E'));

        cout << "Enter the Medicals taken by the Patient (-1) to quit: ";
        string medical;
        while (true)
        {
            cin >> medical;
            if (medical == "-1")
                break;
            MedicalTaken.push_back(medical);
        }

        cout << "Enter an Addtional Note: ";
        getline(cin >> ws, Note);

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

        string fullName, bDay, adress, tel, ABO;
        char FM;

        cout << "Enter the name of the patient : ";
        getline(cin >> ws, fullName);
        cout << "Enter the Adress of the patient : ";
        getline(cin >> ws, adress);
        cout << "Enter the Birth Date of the patient \" dd/mm/yyyy \" : ";
        cin >> bDay;
        cout << "Enter the gender of the patient ( M for male & F for female) : ";
        cin >> FM;
        cout << "Enter the blood type of the patient : ";
        cin >> ABO;
        cout << "Enter the phone number of the patient : ";
        cin >> tel;

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

        char Depart;

        while (true)
        {
            cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
            cout << "Dear Doctor, Please Pick An Option Among The Following Ones, Concerning the Hospital: (Enter The Character That is corresponding to the desired option) \n"
                 << "Depart) Add A Patient\n"
                 << "u) Update The Information Of an Existing Patient\n"
                 << "r) Remove A Patient\n"
                 << "s) Search For Depart Patient (Check if Depart Patient already exists)\n"
                 << "l) Patient is leaving Hospital\n"
                 << "p) Display Patient\n"
                 << "m) Move Patient to Department\n"
                 << "h) Display All History of the Desired Patient\n"
                 << "q) Quit The Program\n"
                 << "Your Input: ";
            cin >> Depart;
            cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
            switch (Depart)
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
                do
                {
                    cout << "\nEnter the ID of the Existing Patient Desired to be Updated: ";
                    cin >> ID;
                } while (!checkId(ID));

                MedicalInfo medInfo = EnterMedicalinfos();
                Hospital.update(ID, medInfo);
                break;
            }
            case 'r':
            {
                string ID;
                do
                {
                    cout << "\nEnter the ID of the Existing Patient Desired to be Removed: ";
                    cin >> ID;
                } while (!checkId(ID));

                Hospital.deletePatient(ID);
                break;
            }
            case 's':
            {
                string ID;
                do
                {
                    cout << "\nEnter the ID of the Patient you want to check its Existence: ";
                    cin >> ID;
                } while (!checkId(ID));

                cout << (Hospital.contains(ID) ? "\nPatient already exists\n" : "\nPatient does not exists\n");
                break;
            }
            case 'l':
            {
                string ID;
                do
                {
                    cout << "\nEnter the ID of the Existing Patient Desired to Leave: ";
                    cin >> ID;
                } while (!checkId(ID));

                Hospital.LeaveHospital(ID);
                break;
            }
            case 'p':
            {
                string ID;
                do
                {
                    cout << "\nEnter the ID of the Existing Patient Desired to be Displayed: ";
                    cin >> ID;
                } while (!checkId(ID));

                Hospital.printPatient(ID);
                break;
            }
            case 'm':
            {
                string ID;
                do
                {
                    cout << "\nEnter the ID of the Existing Patient Desired to be Moved: ";
                    cin >> ID;
                } while (!checkId(ID));
                char dep;
                cout << "Enter the new desired Departement: ";
                cin >> dep;

                Hospital.MoveToDepartement(ID, dep);
                break;
            }
            case 'h':
            {
                string ID;
                do
                {
                    cout << "\nEnter the ID of the Existing Patient Desired to Display its History: ";
                    cin >> ID;
                } while (!checkId(ID));

                vector<MedicalInfo>
                    allHistory = FileHandler().getAllHistory(ID);
                for (const MedicalInfo &info : allHistory)
                    info.printInfo();
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