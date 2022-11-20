#ifndef HOSPITAL_H

#define HOSPITAL_H

#include <iostream>
#include "Patient.h"
#include "Btree.h"
#include "FileHandler.h"
#include <vector>

using std::cout;
using std::vector;

template <typename T>
class Hospital
{
private:
    vector<T> Departements;
    int capacity;
    int numberOfPatients;

public:
    Hospital(int capacity = 1000) : capacity(capacity)
    {
        init();
    }
    void init()
    {
        Departements(NUMBER_OF_DEPARTMENTS);
        vector<vector<Patient>> allPatients = FileHandler().getALLPatient();

        for (int i = 0; i < allPatients.size(); i++)
        {
            Departements[i].insertSortedArray(allPatients[i]);
        }
    }
    void insert(const Patient &patient)
    {

        Departements[patient.getDepartment() - 'A'].insert(patient);
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
                cout << "Deleted Patient Successfully With ID : " << ID << endl;
                return;
            }
        }
        cout << "Could not delete patient With the ID: " << ID << endl
    }

    void update(const string &ID, const MedicalInfo &info)
    {
        for (T &Tree : Departements)
        {
            if (Tree.update(ID, info))
                return;
        }
        cout << "Could not update patient with the ID: " << ID << endl;
        cout << "You may want to create a new patient" << endl;
    }

    bool contains(const string &ID)
    {
        for (T &Tree : Departements)
        {
            if (Tree.contains(ID))
                return true
        }
        return false;
    }

    void printPatient(const string &ID)
    {
        for (T &Tree : Departements)
        {
            if (Tree.printPatient(ID))
                return true;
        }
        return false;
    }
};

#endif