#include "AppInfo.h"
#include "DySySim.h"
#include "LibInfoDySySim.h"

#include <fstream>
#include <iomanip>
#include <iostream>

namespace dss = dysysim;

int main(int argc, char *argv[])
{
   std::cout << "-- " APPNAME_VERSION " " << std::string(50, '-') << "\n"
             << "-- uses " + dss::libName + " " << dss::libVersion << "\n\n";

   // Initial conditions
   const double delta_t{0.025};
   const double RCtime{0.47};

   // Model
   dss::Time time;
   time.config({1, {}, {delta_t}});

   dss::Step step;
   step.config({2, {}, {0, 3000, 0.0}});
   dss::Summator sum;
   sum.config({3, {}, {}});
   dss::OnOff onoff;
   onoff.config({4, {}, {0, 4000, 0}});
   dss::FirstOrder RCcircuit;
   RCcircuit.config({5, {}, {RCtime, 0.0}});

   double setpoint{0.0};
   double error{0.0};
   double control{0.0};

   std::ofstream simdata;
   if (argc == 2) {
      simdata.open(argv[1]);
   }

   int tnMax{8 * int(RCtime / delta_t)};

   for (int tn = 0; tn < tnMax; ++tn) {
      setpoint = step.output();

      sum.input(setpoint, -RCcircuit.output());
      error = sum.output();

      onoff.input(error);
      control = onoff.output();

      std::cout << std::setw(4) << tn << "  t = " << std::setw(5)
                << time.output() << "  Setpoint = " << std::setw(5) << setpoint
                << "  Control = " << std::setw(5) << control
                << "  Measured Value = " << std::setw(8) << RCcircuit.output()
                << std::endl;

      if (argc == 2) {
         simdata << std::setw(4) << time.output() << " " << setpoint << " "
                 << control << " " << RCcircuit.output() << std::endl;
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
