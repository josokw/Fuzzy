#include "AppInfo.h"
#include "Defuzzification.h"
#include "FuzzyLogic.h"
#include "InputFuzzySetTriangular.h"
#include "InputFuzzySetTrapezoidal.h"
#include "OutputFuzzySetTriangular.h"

#include <array>
#include <iostream>
#include <string>

using namespace std;

int main()
{
  cout << "-- " APPNAME_VERSION " ----------------------------" << endl << endl;

  // Linguistic variable Service
  InputFuzzySetTriangular poor("Service = poor", 0, 2.5 ,5);
  InputFuzzySetTriangular good("Service = good", 2.5, 5 ,7.5);
  InputFuzzySetTriangular great("Service = great", 5, 7.5, 10);
  // Liguistic variable Food
  InputFuzzySetTrapezoidal rancid("Food = rancid", 0, 0, 1.5, 4);
  InputFuzzySetTrapezoidal delicious("Food = delicious", 6, 8.5, 10, 10);
  // Linguistic variable Tip
  OutputFuzzySetTriangular cheap("Tip = cheap", 0, 5, 10);
  OutputFuzzySetTriangular average("Tip = average", 10, 15, 20);
  OutputFuzzySetTriangular generous("Tip = generous", 20, 25, 30);
  // Polymorfic arrays
  std::array<InputFuzzySet*, 3> fuzzyService{&poor, &good, &great};
  std::array<InputFuzzySet*, 2> fuzzyFood{&rancid, &delicious};
  std::array<OutputFuzzySet*, 3> fuzzyTip{&cheap, &average, &generous};

  for(int food = 0; food < 11; ++food) {
      for(int service = 0; service < 11; ++service) {
          cout << "-------- Service = "<< service << " Food = " << food << endl;
          // Set inputs
          for(auto& fs : fuzzyService) {
              fs->setInput(service);
              cout << *fs << endl;
            }
          for(auto& fs : fuzzyFood) {
              fs->setInput(food);
              cout << *fs << endl;
            }
          // Rule base
          cheap = poor or rancid;
          average = good;
          generous = great or delicious;
          // Defuzzification
          cout << "-- MOM Tip = " << int(defuzMeanOfMaximum<3>(fuzzyTip))
               << "%" << endl;
          cout << "-- FOM Tip = " << int(defuzFirstOfMaxima<3>(fuzzyTip))
               << "%" << endl;
          cout << "-- LOM Tip = " << int(defuzLastOfMaxima<3>(fuzzyTip))
               << "%" << endl;
          cout << "-- WA  Tip = " << int(defuzWeightedAverage<3>(fuzzyTip))
               << "%" << endl;

          getchar();
        }
    }

  return 0;
}
