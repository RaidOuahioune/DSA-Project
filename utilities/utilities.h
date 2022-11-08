#ifndef Utils_h
#define Utils_h
#include <iomanip>
#include <ctime>
#include <sstream>
#include <vector>
#include <fstream>
#include <random>
#include <filesystem>
using std::ifstream;
using std::put_time;
using std::string;
using std::stringstream;
using std::vector;

bool is_file_exist(const string &fileName)
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

string generateID(int seed)
{
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);

  std::ostringstream oss;
  // we have chosen the ID by time, so that we are sure that it is unique
  oss << std::put_time(&tm, "%d%m%Y%H%M");

  /* std::cout << rand() % 10 << std::endl;
  std::cout << rand() % 10; */

  const int range_from = 10;
  const int range_to = 99;
  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  std::uniform_int_distribution<int> distr(range_from, range_to);

  /*   srand(t);
   */
  return (std::to_string((distr(generator))) + oss.str().erase(4, 2));
  // FIRST: WE GENERATE A RANDOM TWO DIGITS NUMBER SO IT'S FROM 10 TO 99 AND THEN WE STRINGIFIED IT
  // SECOND: WE GENERATE THE ACTUAL DATE WITH TIME AND SECONDS, AND WE REMOVED THE "20" FROM THE "2022" OF THE FULL DATE
}

vector<string> getAllFiles()
{
  std::filesystem::directory_iterator end_itr;
  vector<string> files;
  for (std::filesystem::directory_iterator itr("Data"); itr != end_itr; ++itr)
  {
    files.push_back(itr->path().string());
  }
  return files;
}
#endif