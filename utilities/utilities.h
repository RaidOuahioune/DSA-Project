#ifndef Utils_h
#define Utils_h
#include <iomanip>
#include <ctime>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp>
using std::ifstream;
using std::put_time;
using std::string;
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
  boost::split(medicals, sentence, boost::is_any_of(", "), boost::token_compress_on);
  return medicals;
}

#endif