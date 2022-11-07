#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "../Interfaces/Patient.h"
#include <fstream>
using std::ifstream;
using std::ofstream;
class FileHandler
{
public:
  FileHandler(){};
  void InsertMedicalInfo(const MedicalInfo &, const string ID) const; // this function Insert the new inforamtion to the desired file given that the file already exists
  void InsertFullData(const Patient &) const;                         // Create a new file with current patient information
  vector<MedicalInfo> getAllHistory(const string &ID) const;
  ~FileHandler() {}

private:
};
void FileHandler::InsertMedicalInfo(const MedicalInfo &info, const string ID) const
{
  ofstream file;
  string FilePath = "Data/" + ID + ".txt";
  file.open(FilePath, std::ios_base::app);
  if (file)
  {
    
    file << "CD: " << info.CD << endl;
    file << "Allergies: " << info.Allergies << endl;
    file << "BP: " << info.BP << endl;
    file << "HR: " << info.HR << endl;
    file << "Medicals Taken: ";
    for (const string &medical : info.MedicalsTaken)
      file << medical << " ";
    file << endl;
    file << "Time: " << info.time << endl;
    file << "Department: " << info.Department << endl;
    file << "Notes: " << info.briefNote << endl;
    file << endl;
  }
  else
  {
    throw "Exception";
  }

  file.close();
}

vector<MedicalInfo> FileHandler::getAllHistory(const string &ID) const
{
  vector<MedicalInfo> output;
  ifstream file;
  file.open("Data/" + ID + ".txt");
  if (file)
  { // we read line by line

    string line;
    // we skip the first 8 lines of the genaral information
    for (int i = 0; i < 8; ++i)
      getline(file, line);

    // Medical Info Object to be pushed to the output vector
    MedicalInfo info;

    int counter = 0; // counter to indicate the type of information included in the current line

    while (getline(file, line))
    {
      if (counter != 8)
      {
        if (counter == 0)
          info.CD = line.substr(string("CD: ").size());

        else if (counter ==1)

          info.Allergies = line.substr(string("Allergies: ").size());

        else if (counter == 2)

          info.BP = stof(line.substr(string("BP: ").size()));

        else if (counter == 3)

          info.HR = stof(line.substr(string("HR: ").size()));

        else if (counter == 4)

          info.MedicalsTaken = getVector(line.substr(string("Medicals Taken: ").size())); // Construct the vecotor of Medicals

        else if (counter == 5)

          info.time = line.substr(string("Time: ").size());

        else if (counter == 6)

          info.Department = line.substr(string("Department: ").size())[0];

        else if (counter == 7)

          info.briefNote = line.substr(string("Notes: ").size());

        // incrementing the counter is included in every case
        counter++;
      }

      else
      {
        // This is an empty line so ignore it
        // we push the Object to output vector since all its data members are filled
        counter = 0;
        output.push_back(info);
      }
    }
  }
  else
    std::cout << "File not found !(test Only)" << endl;

  file.close();

  return output;
}

void FileHandler::InsertFullData(const Patient &patient) const
{
  string path = "Data/" + patient.ID + ".txt";
  MedicalInfo info = patient.getMedicalInfo();
  if (is_file_exist(path))
  {
    cout << "File already exists" << endl;
    return;
  }
  else
  {
    ofstream file;
    file.open(path, std::ios_base::app);
    if (file)
    {
      // we insert the static Data (genral data that we know it won't change)
      file << "ID: " << patient.ID << endl;
      file << "FullName: " << patient.fullName << endl;
      file << "BirthDay: " << patient.bDay << endl;
      file << "Entry Date: " << patient.entryDate << endl;
      file << "Adress: " << patient.adress << endl;
      file << "Gender: " << patient.FM << endl;
      file << "Telephone: " << patient.tel << endl;
      file << "ABO: " << patient.ABO << endl;
      // Now we insert the medical infos

      file << "CD: " << info.CD << endl;
      file << "Allergies: " << info.Allergies << endl;
      file << "BP: " << info.BP << endl;
      file << "HR: " << info.HR << endl;
      file << "Medicals Taken: ";
      for (const string &medical : info.MedicalsTaken)
        file << medical << " ";
      file << endl;
      file << "Time: " << info.time << endl;
      file << "Department: " << info.Department << endl;
      file << "Notes: " << info.briefNote << endl;
      file << endl;
    }
    else
    {
      throw "Exception";
    }

    file.close();
  }
}

#endif