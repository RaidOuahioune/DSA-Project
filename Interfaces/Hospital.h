// Leader Full Name: Ouahioune Raid Abderrezak 

//Group:4

#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <iostream>
#include <unordered_map>
#include "Patient.h"
#include "../Part1/Btree.h"
#include "../utilities/FileHandler.h"
#include <vector>
#include <string>

using std::cout;
using std::pair;
using std::unordered_map;
using std::vector;
template <typename T>
class Hospital
{

public:
    Hospital(int capacity = 10000000) : capacity(capacity), Departements(NUMBER_OF_DEPARTMENTS), numberOfPatients(0)
    {
        init();
    }
    ~Hospital()
    {
        for (const Patient &patient : insertedPatients)
        {
            CreateFile(patient);
        }
        for (pair<string, MedicalInfo> element : updatedPatients)

        {
            ExtendFile(element.first, element.second);
        }
    }
    void RemoveAllHistory(const string &ID)
    {
        const char *path = "Data/" + ID + ".txt";
        if (is_file_exist(path))

            remove(path);
        else
            cout << "\nHISTORY OF THE GIVEN ID DOES NOT EXIST" << endl;
    }

    void insert(const Patient &patient)
    {
        if (!isCapacityReached())
            if (Departements[patient.getDepartment() - 'A'].insert(patient))
            {
                insertedPatients.push_back(patient);
            };

        cout << "\nWARNING CAPACITY OF HOSPITAL WAS REACHED" << endl;
    }

    void deletePatient(const string &ID)
    {
        bool isBtree = std::is_same<T, BTree>::value;
        bool state = isBtree;

        for (T &Tree : Departements)
        {
            Tree.Delete(ID, state);

            if ((isBtree && state) || (!isBtree && state))
            {
                cout << "\nDeleted Patient Successfully With ID : " << ID << endl;
                return;
            }
            state = isBtree;
        }
        cout << "\nCould not delete patient With the ID: " << ID << endl;
    }

    void update(const string &ID, const MedicalInfo &info)
    {
        for (T &Tree : Departements)
        {
            if (Tree.update(ID, info))
            {
                updatedPatients[ID] = info;
                return;
            }
        }
        cout << "\nCould not update patient with the ID: " << ID << endl;
        cout << "You may want to create a new patient" << endl;
    }

    bool contains(const string &ID)
    {
        for (T &Tree : Departements)
        {
            if (Tree.contains(ID))
                return true;
        }
        return false;
    }

    void printPatient(const string &ID)
    {

        for (T &Tree : Departements)
        {
            if (Tree.printPatient(ID))
                return;
        }
    }
    void LeaveHospital(const string &ID)
    {
        MedicalInfo info;
        info.setAllergies("");
        info.setBP(0);
        info.setHr(0);
        info.setNote("Left Hospital");
        info.setMedicalstaken({});
        info.setCd("");
        info.setDepartment('N');
        this->update(ID, info);
    }
    void MoveToDepartement(const string &ID, const char &a)
    {

        if (a == 'A' || a == 'B' || a == 'C' || a == 'D' || a == 'E' || a == 'N')
        {
            MedicalInfo info;
            for (T &Tree : Departements)
            {
                if (Tree.update(ID, a, info))
                {
                    updatedPatients[ID] = info;
                    return;
                }
            }
            cout << "\nCould not update patient with the ID: " << ID << endl;
            cout << "You may want to create a new patient" << endl;
        }
    }

private:
    vector<T> Departements;
    int capacity;
    int numberOfPatients;
    vector<Patient> insertedPatients;
    unordered_map<string, MedicalInfo> updatedPatients;
    void CreateFile(const Patient &patient) const
    {
        FileHandler handler;
        if (is_file_exist("Data/" + patient.getId() + ".txt"))
            handler.InsertMedicalInfo(patient.getMedicalInfo(), patient.getId());
        else
            cout << "\nWARNING ATTEMPT TO CREATE AN ALREADY EXSITED FILE" << endl;
    }

    void ExtendFile(const string &ID, const MedicalInfo &info)
    {
        FileHandler().InsertMedicalInfo(info, ID);
    }
    void init()
    {
        cout << "\nInitializing The Hospital .............." << endl;
        vector<vector<Patient>> allPatients = FileHandler().getALLPatient();

        for (int i = 0; i < allPatients.size(); i++)
        {

            numberOfPatients += allPatients[i].size();
            Departements[i].InsertSortedArray(allPatients[i]);
        }
    }
    bool isCapacityReached()
    {
        return numberOfPatients >= capacity;
    }
};

#endif