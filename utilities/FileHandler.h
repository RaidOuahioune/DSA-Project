// Leader Full Name :Ouahioune Raid Abderrezak
// Group: G4
#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "../Interfaces/Patient.h"
#include "utilities.h"
#include <fstream>
#include <chrono>
using std::ifstream;
using std::ios;
using std::ofstream;

const int NUMBER_OF_DEPARTMENTS = 5;
class FileHandler
{
public:
  FileHandler(){};
  void InsertMedicalInfo(const MedicalInfo &, const string ID) const; // this function Insert the new inforamtion to the desired file given that the file already exists
  void InsertFullData(const Patient &) const;                         // Create a new file with current patient information
  vector<MedicalInfo> getAllHistory(const string &ID) const;
  vector<vector<Patient>> getALLPatient(int &) const;
  vector<vector<Patient>> getALLPatient() const;
  ~FileHandler() {}

private:
  Patient BuildPatient(const string &file) const;
  MedicalInfo getRecentMedicalInfo(const string &file) const;
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

        else if (counter == 1)

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
      cout << "Error Occured when Trying to read a file" << endl;
    }

    file.close();
  }
}
#ifdef _WIN32
vector<vector<Patient>> FileHandler::getALLPatient(int &size) const
{

  vector<vector<Patient>> vec(NUMBER_OF_DEPARTMENTS);
  string file;
  Patient patient;
  for (const auto &entry : fs::directory_iterator("Data"))
  {
    file = (entry.path().string()).substr(5);
    size++;
    patient = BuildPatient(file);
    if (patient.getDepartment() != 'N')
      vec[patient.getDepartment() - 'A'].push_back((patient));
  }

  return vec;
}

vector<vector<Patient>> FileHandler::getALLPatient() const
{

  vector<vector<Patient>> vec(NUMBER_OF_DEPARTMENTS);
  string file;
  Patient patient;
  for (const auto &entry : fs::directory_iterator("Data"))
  {
    file = (entry.path().string()).substr(5); // without /Data
    patient = BuildPatient(file);
    if (patient.getDepartment() != 'N')
      vec[patient.getDepartment() - 'A'].push_back((patient));
  }

  return vec;
}

#else
vector<vector<Patient>> FileHandler::getALLPatient(int &size) const
{

  vector<vector<Patient>> vec(NUMBER_OF_DEPARTMENTS);
  char buffer[128];
  const char *command;
  command = "cd Data && ls";

  // Open pipe to file
  FILE *pipe = popen(command, "r");
  if (!pipe)
  {
    return vec;
  }
  string file;
  Patient patient;
  // read till end of process:
  while (!feof(pipe))
  {
    // use buffer to read and add to result
    if (fgets(buffer, 128, pipe) != NULL)
    {
      size++;
      file = string(buffer).erase(18);
      patient = BuildPatient(file);
      if (patient.getDepartment() != 'N')
        vec[patient.getDepartment() - 'A'].push_back((patient));
    }
  }
  pclose(pipe);
  return vec;
}
vector<vector<Patient>> FileHandler::getALLPatient() const
{

  vector<vector<Patient>> vec(NUMBER_OF_DEPARTMENTS);
  char buffer[128];

  const char *command;

  command = "cd Data && ls";

  // Open pipe to file
  FILE *pipe = popen(command, "r");
  if (!pipe)
  {
    return vec;
  }
  string file;
  Patient patient;
  // read till end of process:
  while (!feof(pipe))
  {
    // use buffer to read and add to result
    if (fgets(buffer, 128, pipe) != NULL)
    {
      file = string(buffer).erase(18);
      patient = BuildPatient(file);
      if (patient.getDepartment() != 'N')
        vec[patient.getDepartment() - 'A'].push_back((patient));
    }
  }
  pclose(pipe);
  return vec;
}

#endif
Patient FileHandler::BuildPatient(const string &file) const
{

  string path = "Data/" + file;
  Patient patient;
  ifstream rfile;
  rfile.open(path);
  int counter = 0;
  string line;
  if (rfile)
  {
    // writing the general inforamtion of the patient
    while (getline(rfile, line) && counter <= 7)
    {
      if (counter == 0)
        patient.ID = line.substr(string("ID: ").size());
      else if (counter == 1)
        patient.fullName = line.substr(string("FullName: ").size());
      else if (counter == 2)
        patient.bDay = line.substr(string("BirthDay: ").size());
      else if (counter == 3)
        patient.entryDate = line.substr(string("Entry Date: ").size());
      else if (counter == 4)
        patient.adress = line.substr(string("Adress: ").size());
      else if (counter == 5)
        patient.FM = line.substr(string("Gender: ").size())[0];
      else if (counter == 6)
        patient.tel = line.substr(string("Telephone: ").size());
      else if (counter == 7)
        patient.ABO = line.substr(string("ABO: ").size());
      counter++;
    }
  }
  rfile.close();
  patient.MI = getRecentMedicalInfo(file);
  return patient;
}

MedicalInfo FileHandler::getRecentMedicalInfo(const string &file) const
{
  MedicalInfo info;
  string path = "Data/" + file;

  ifstream in(path, ios::binary);
  in.seekg(0, ios::end);

  string line;
  char ch;
  bool char_seen = false;

  in.seekg(-1, ios::cur);
  int counter = 0;
  while (in.get(ch) && counter <= 8)
  {
    if (ch == '\n' && char_seen)
    {
      auto pos = in.tellg();
      getline(in, line);

      if (counter != 0)
      {
        if (counter == 1)
          info.briefNote = line.substr(string("Notes: ").size());
        else if (counter == 2)
          info.Department = line.substr(string("Department: ").size())[0];
        else if (counter == 3)
          info.time = line.substr(string("Time: ").size());
        else if (counter == 4)
          info.MedicalsTaken = getVector(line.substr(string("Medicals Taken: ").size()));
        else if (counter == 5)
          info.HR = stof(line.substr(string("HR: ").size()));
        else if (counter == 6)
          info.BP = stof(line.substr(string("BP: ").size()));
        else if (counter == 7)
          info.Allergies = line.substr(string("Allergies: ").size());
        else if (counter == 8)
          info.CD = line.substr(string("CD: ").size());
      }
      counter++;

      // cout << line << endl;
      in.clear();
      in.seekg(pos);
    }
    char_seen = true;
    in.clear();
    in.seekg(-2, ios::cur);
  }
  return info;
}

#endif