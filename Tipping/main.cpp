#include "AppInfo.h"
#include "TippingFIS.h"

#include <array>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

void doTippingFIS(std::ostream &os, TippingFIS &tfis, DEFUZ defuzzification);

int main() {
   cout << "-- " APPNAME_VERSION << " " << string(50, '-') << endl << endl;

   TippingFIS tippingFIS;

   cout << tippingFIS << endl;

   cout << "-- Defuzzification: Mean of Maximum" << endl << endl;
   doTippingFIS(cout, tippingFIS, DEFUZ::MoM);

   cout << "-- Defuzzification: First of Maxima" << endl << endl;
   doTippingFIS(cout, tippingFIS, DEFUZ::FoM);

   cout << "-- Defuzzification: Last of Maxima" << endl << endl;
   doTippingFIS(cout, tippingFIS, DEFUZ::LoM);

   cout << "-- Defuzzification: Weighted Average" << endl << endl;
   doTippingFIS(cout, tippingFIS, DEFUZ::WA);

   return 0;
}

void doTippingFIS(std::ostream &os, TippingFIS &tfis, DEFUZ defuzzification) {
   os << " service" << endl << endl;
   for(int service = 0; service < 11; ++service) {
      os << setw(8) << service << "  ";
      for(int food = 0; food < 11; ++food) {
         os << setw(5) << tfis.inferTip(food, service, defuzzification);
      }
      os << endl;
   }
   os << endl << "    food  ";
   for(int food = 0; food < 11; ++food) {
      os << setw(5) << food;
   }
   os << endl << endl;
}
