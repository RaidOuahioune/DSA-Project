#include <iostream>
#include "Part1/Btree.h"
#include "Part3/AVL.h"
#include "Part2/BST.h"
#include "utilities/FileHandler.h"
#include "Test/generalTesting.h"
#include "Test/BtreeComparaison.h"
#include <filesystem>
using namespace std;
//
int main()
{
  FileHandler handler;
  vector<AvlTree> BSTtree(NUMBER_OF_DEPARTMENTS);
  vector<vector<Patient>> allPatients = handler.getALLPatient();

  for (int y = 0; y < NUMBER_OF_DEPARTMENTS; y++)
  {
    BSTtree[y].InsertSortedArray(allPatients[y]);
  }
  for (int y = 0; y < NUMBER_OF_DEPARTMENTS; y++)
    cout << BSTtree[y].getNumberOfPatient() << endl;
}
