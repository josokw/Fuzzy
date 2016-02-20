#include "AppInfo.h"
#include "DySySim.h"
#include "LibInfoDySySim.h"
#include <iomanip>
#include <iostream>

namespace dss = dysysim;
using namespace std;

int main()
{
   cout << "-- " APPNAME_VERSION " " << string(50, '-') << endl
        << "-- uses " + dss::libName + " " << dss::libVersion << endl << endl;

   const double Tsimulation{0.005};
   const double RCtime{0.47};
   // Model
   dss::Time time{1, Tsimulation};
   dss::Step step{2, 0, 3000, 0};
   dss::Summator sum{3};
   dss::OnOff onoff{4, 0, 4000, 0};
   dss::FirstOrder RCcircuit{5, RCtime, 0};

   dss::Log logger({1,2,3,4,5});

   double setpoint{0.0};
   double error{0.0};
   double control{0.0};

   logger.next(); // tn = 0

   for(int tn = 0; tn < 1000; ++tn) {
       step.next();
       setpoint = step.output();
       sum.input(setpoint, -RCcircuit.output());
       error = sum.output();
       onoff.input(error);
       control = onoff.output();
       RCcircuit.input(control);

       cout << setw(4) << tn << "  t = " << setw(5) << time.output()
            << "  Setpoint = " << setw(6) << setpoint
            << "  Control = " << setw(6) << control
            << "  Measured Value = " << setw(10)
            << RCcircuit.output() << endl;

       logger.next();
       time.next();
       getchar();
   }

   return 0;
}

