#include "AppInfo.h"
#include "TippingFIS.h"

#include <array>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

void doTippingFIS(TippingFIS& tfis, DEFUZ defuzzification);

int main()
{
   cout << "-- " APPNAME_VERSION << " " << string(50, '-') << endl << endl;

   TippingFIS tippingFIS;

   cout << tippingFIS << endl;

   cout << "-- Defuzzification: Mean of Maximum" << endl << endl;
   doTippingFIS(tippingFIS, DEFUZ::MoM);
   cout << "-- Defuzzification: First of Maxima" << endl << endl;
   doTippingFIS(tippingFIS, DEFUZ::FoM);
   cout << "-- Defuzzification: Last of Maxima" << endl << endl;
   doTippingFIS(tippingFIS, DEFUZ::LoM);
   cout << "-- Defuzzification: Weighted Average" << endl << endl;
   doTippingFIS(tippingFIS, DEFUZ::WA);

   return 0;
}

void doTippingFIS(TippingFIS& tfis, DEFUZ defuzzification) {
   cout << " service " << endl << endl;
   for(int service = 0; service < 11; ++service) {
      cout << setw(8) << service;
      for(int food = 0; food < 11; ++food) {
         cout << setw(5) << tfis.inferTip(food, service, defuzzification);
      }
      cout << endl;
   }
   cout << endl << "    food";
   for(int food = 0; food < 11; ++food) {
      cout << setw(5) << food;
   }
   cout << endl << endl;
}
