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
using std::fstream;
using std::ifstream;
using std::put_time;
using std::string;
using std::stringstream;
using std::to_string;
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
    files.push_back(string(entry.path()).substr(5));

  return files;
}
string generateBDay()
{
  srand(time(0));

  int year = 1930 + rand() % 92;
  int mounth = rand() % 13;
  int day = rand() % 30;
  string sday = (day < 10) ? "0" + to_string(day) : to_string(day);
  string smounth = (mounth < 10) ? "0" + to_string(mounth) : to_string(mounth);
  return sday + "-" + smounth + "-" + to_string(year);
}

string generateABO()
{

  string ABOTypes[4] = {"A", "B", "AB", "O"};
  srand(time(nullptr));
  string sign = (rand() % 2 == 0) ? "+" : "-";
  return ABOTypes[rand() % 4] + sign;
}
string generateTel()
{

  srand(time(nullptr));

  string beg = to_string(rand() % 3 + 5);
  return "0" + beg + to_string(rand() % 100000000);
}
char generateFM()
{
  srand(time(nullptr));
  return (rand() % 2 == 0) ? 'M' : 'F';
}
string generateFUllName()
{
  ifstream file;
  string line;
  file.open("utilities/Source/Names.txt");
  srand(time(nullptr));
  int random1 = rand() % 18239;
  int random2 = rand() % 18239;
  while (random2 == random1)
    random2 = rand() % 18239;
  int counter = 0;
  int stoper = 0;
  string result;
  while (getline(file, line) && stoper < 2)

  {
    if (counter == random1 || counter == random2)
    {
      stoper++;
      result += line + " ";
    }
    counter++;
  }
  file.close();

  return result;
}
vector<string> generateMedicals()
{
  vector<string> result;
  srand(time(nullptr));

  int rand1 = 1 + rand() % 3;

  ifstream file;
  string line;
  file.open("utilities/Source/medicals.txt");

  int random1 = rand() % 301;
  int random2 = rand() % 301;
  int random3 = rand() % 301;
  while (random2 == random1 || random3 == random1)
  {
    random3 = rand() % 301;
    random2 = rand() % 301;
  }
  int counter = 0;
  int stoper = 0;
  while (getline(file, line) && stoper < rand1)

  {
    if (counter == random1 || counter == random2 || counter == random3)
    {
      stoper++;
      result.push_back(line);
    }
    counter++;
  }
  file.close();

  return result;
}
float randMToN(float M, float N)
{
  srand(time(nullptr));
  return M + (rand() / (RAND_MAX / (N - M)));
}
float generateHB()
{
  return randMToN(30.5, 200);
}
float generateBP()
{
  return randMToN(90.01, 140.03);
}

string generateAllergies()
{
  ifstream file;
  string line;
  file.open("utilities/Source/allergies.txt");
  srand(time(nullptr));
  int rand1 = rand() % 4;
  int random1 = rand() % 14;
  int random2 = rand() % 14;
  int random3 = rand() % 14;
  while (random2 == random1 || random3 == random1)
  {
    random2 = rand() % 14;
    random3 = rand() % 14;
  }

  int counter = 0;
  int stoper = 0;
  string result;
  while (getline(file, line) && stoper < rand1)

  {
    if (counter == random1 || counter == random2 || counter == random3)
    {
      stoper++;
      result += line + " ";
    }
    counter++;
  }
  file.close();

  return result;
}

string generateCDS()
{
  ifstream file;
  string line;
  file.open("utilities/Source/chronic.txt");
  srand(time(nullptr));
  int rand1 = rand() % 3;
  int random1 = rand() % 18;
  int random2 = rand() % 18;
  int random3 = rand() % 18;
  while (random2 == random1 || random3 == random1)
  {
    random2 = rand() % 18;
    random3 = rand() % 18;
  }

  int counter = 0;
  int stoper = 0;
  string result;
  while (getline(file, line) && stoper < rand1)

  {
    if (counter == random1 || counter == random2 || counter == random3)
    {
      stoper++;
      result += line + " ";
    }
    counter++;
  }
  file.close();
  return result;
}

string generateAdress()
{
  ifstream file1;
  ifstream file2;
  string line;
  file1.open("utilities/Source/states.txt");
  file2.open("utilities/Source/streets.txt");
  srand(time(nullptr));
  int random1 = rand() % 48;
  int random2 = rand() % 2704;

  int counter = 0;

  string result;
  while (getline(file1, line))
  {
    if (counter == random1)
    {
      result += line + "/";
      break;
    }
    counter++;
  }
  while (getline(file2, line))
  {
    if (counter == random2)
    {
      result += line + "/";
      break;
    }
    counter++;
  }

  counter = 0;
  file1.close();
  file2.close();
  return result + "Block:" + char(65 + rand() % 27) + "/dep:" + to_string(1 + rand() % 200);
}

#endif