#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "../Interfaces/Patient.h"
#include <fstream>
using std::ifstream;
using std::ofstream;
class FileHandler
{
public:
  FileHandler(const string &);
  void InsertMedicalInfo(const MedicalInfo &) const; // this function Insert the new inforamtion to the desired file given that the file already exists
  void InsertFullData(const Patient &) const;        // Create a new file with current patient information
  vector<MedicalInfo> getAllHistory() const;
  ~FileHandler() {}

private:
  string FilePath; // THE PATh of the file where Patient Data is recorded
  // each file stores all the Historical data of exactly one patient
};

FileHandler::FileHandler(const string &path) : FilePath(path) {}

void FileHandler::InsertMedicalInfo(const MedicalInfo &info) const
{
  ofstream file;
  file.open(this->FilePath, std::ios_base::app);
  if (file)
  {
    file << "ABO: " << info.ABO << endl;
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

vector<MedicalInfo> FileHandler::getAllHistory() const
{
  vector<MedicalInfo> output;
  ifstream file;
  file.open(this->FilePath);
  if (file)
  { // we read line by line

    string line;
    // we skip the first 10 lines of the genaral information
    for (int i = 0; i <= 9; ++i)
      getline(file, line);

    // Medical Info Object to be pushed to the output vector
    MedicalInfo info;

    int counter = 0; // counter to indicate the type of information included in the current line

    while (getline(file, line))
    {
      if (counter != 9)
      {
        if (counter == 0)

          info.ABO = line.substr(string("ABO: ").size());

        else if (counter == 1)

          info.CD = line.substr(string("CD: ").size());

        else if (counter == 2)

          info.Allergies = line.substr(string("Allergies: ").size());

        else if (counter == 3)

          info.BP = stof(line.substr(string("BP: ").size()));

        else if (counter == 4)

          info.HR = stof(line.substr(string("HR: ").size()));

        else if (counter == 5)

          info.MedicalsTaken = getVector(line.substr(string("Medicals Taken: ").size())); // Construct the vecotor of Medicals

        else if (counter == 6)

          info.time = line.substr(string("Time: ").size());

        else if (counter == 7)

          info.Department = line.substr(string("Department: ").size())[0];

        else if (counter == 8)

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
}

#endif