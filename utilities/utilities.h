#ifndef Utils_h
#define Utils_h

#include <iomanip>
#include <ctime>
#include <sstream>
#include <vector>
#include <fstream>

using std::ifstream;
using std::put_time;
using std::string;
using std::stringstream;
using std::vector;

bool is_file_exist(const char *fileName)
{
  std::ifstream infile(fileName);
  return infile.good();
}

string getTime()
{
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);

  std::ostringstream oss;
  oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");

  return oss.str();
}

vector<string> getVector(const string &sentence)
{
  vector<string> medicals;
  stringstream ss(sentence);
  string words;
  while (ss >> words)
    medicals.push_back(words);

  return medicals;
}

#endif