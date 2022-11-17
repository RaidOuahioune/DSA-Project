#ifndef Utils_h
#define Utils_h
#include <iomanip>
#include <ctime>
#include <sstream>
#include <vector>
#include <fstream>
#include <random>
#include <filesystem>
#include <filesystem>
using std::ifstream;
using std::put_time;
using std::string;
using std::stringstream;
using std::vector;
namespace fs = std::filesystem;

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

vector<string> getFiles()
{
  char buffer[128];

  const char *command;

  command = "cd Data && ls";

  vector<string> files;

  // Open pipe to file
  FILE *pipe = popen(command, "r");
  if (!pipe)
  {
    return files;
  }

  // read till end of process:
  while (!feof(pipe))
  {

    // use buffer to read and add to result
    if (fgets(buffer, 128, pipe) != NULL)
      files.push_back(string(buffer).erase(18));
  }

  pclose(pipe);
  return files;
}
vector<string> getFilesinWin()
{
  std::string path = "Data";
  vector<string> files;

  for (const auto &entry : fs::directory_iterator(path))
    files.push_back(string(entry.path().string()).substr(5));

  return files;
}
#endif