#include "AppInfo.h"
#include "TippingFIS.h"

#include <array>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main()
{
   cout << "-- " APPNAME_VERSION << " " << string(50, '-') << endl << endl;

   TippingFIS tipping;

   cout << " service " << endl << endl;
   for(int service = 0; service < 11; ++service) {
      cout << setw(8) << service;
      for(int food = 0; food < 11; ++food) {
         cout << setw(5) << tipping.inferTip(food, service);
      }
      cout << endl;
   }
   cout << endl << "    food";
   for(int food = 0; food < 11; ++food) {
      cout << setw(5) << food;
   }
   cout << endl << endl;

   return 0;
}
