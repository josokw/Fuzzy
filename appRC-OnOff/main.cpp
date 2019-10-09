#include "AppInfo.h"
#include "DySySim.h"
#include "LibInfoDySySim.h"
#include <fstream>
#include <iomanip>
#include <iostream>

namespace dss = dysysim;
using namespace std;

int main(int argc, char *argv[])
{
   cout << "-- " APPNAME_VERSION " " << string(50, '-') << endl
        << "-- uses " + dss::libName + " " << dss::libVersion << endl
        << endl;

   // Initial conditions
   const double Tsimulation{0.005};
   const double RCtime{0.47};
   // Model
   dss::Time time{1, Tsimulation};
   dss::Step step{2, 0, 3000, 0.0};
   dss::Summator sum{3};
   dss::OnOff onoff{4, 0, 4000, 0};
   dss::FirstOrder RCcircuit{5, RCtime, 0};

   double setpoint{0.0};
   double error{0.0};
   double control{0.0};

   std::ofstream simdata;
   if (argc == 2) {
      simdata.open(argv[1]);
   }

   int tnMax{8 * int(RCtime / Tsimulation)};

   for (int tn = 0; tn < tnMax; ++tn) {
      setpoint = step.output();

      sum.input(setpoint, -RCcircuit.output());
      error = sum.output();

      onoff.input(error);
      control = onoff.output();

      cout << setw(4) << tn << "  t = " << setw(5) << time.output()
           << "  Setpoint = " << setw(5) << setpoint
           << "  Control = " << setw(5) << control
           << "  Measured Value = " << setw(8) << RCcircuit.output()
           << endl;

      if (argc == 2) {
         simdata << setw(4) << time.output() << " " << setpoint << " "
                 << control << " " << RCcircuit.output() << endl;
      }

      RCcircuit.input(control);
      time.next();
      step.next();

      if (argc == 1) {
         getchar();
      }
   }
   simdata.close();

   return 0;
}
