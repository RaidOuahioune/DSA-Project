// Leader Full Name: Ouahioune Raid Abderrezak

// Group:4

#include <iostream>
#include "Interfaces/Hospital.h"
#include "Part1/Btree.h"
#include "Part3/AVL.h"
#include "Part2/BST.h"
#include "utilities/FileHandler.h"
#include "Test/generalTesting.h"
#include "Test/BtreeComparaison.h"
#include "functionalities.h"
#include <filesystem>

using namespace std;
// Namespace Wrapping All Driver Functionalities
using namespace DriverFunctions;

int main()
{
  // IF YOU WANT TO RUN THE SOFTWARE
  //DoctorInput();

  /*IF YOU WANT TO COMPARE BETWEEN THE 3 ADTS*/
  // IF YOU WANT TO GENERATE DATA  ONLY

  // GeneralTesting::GenerateDataOnly();
  // IF YOU WANT TO GENERATE DATA AND TEST
  // GeneralTesting::GenerateDataAndTest();

  /*IF YOU WANT TO COMPARE BETWEEN THE BTRESS*/

  BtreeComparaison::GenerateData();
}
