#include "AppInfo.h"
#include "RCcircuit.h"

#include "Defuzzification.h"
#include "FuzzyLogic.h"
#include "InputFuzzySetTriangular.h"
#include "InputFuzzySetTrapezoidal.h"
#include "OutputFuzzySetTriangular.h"

#include <iostream>

using namespace std;

int main()
{
   // RC circuit
   cout << "-- " APPNAME_VERSION " ----------------------------" << endl << endl;
   const double Ts{0.01};
   const double RCtime{0.2};
   RCcircuit RC{Ts, 0, RCtime};
   double input{0.0};

   // Step function
   for(int i = 0; i < 200; ++i) {
      RC.input(input);
      cout << "t = " << i * Ts << " input = " << input
           << " output = " << RC.output() << endl;
      if (i > 9.0) {
         input = 1.0;
      }
   }

   return 0;
}
