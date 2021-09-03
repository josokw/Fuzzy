
#include "AppInfo.h"
#include "DySySim.h"
#include "LibInfoDySySim.h"

#include <fstream>
#include <iomanip>
#include <iostream>

namespace dss = dysysim;

int main(int argc, char *argv[])
{
   std::cout << "-- " APPNAME_VERSION " "
             << "-- uses " + dss::libName + " " << dss::libVersion << "\n\n";

   // Initial conditions
   const double delta_t{0.005};
   const double RCtime{0.5};

   dss::SimTime::set(delta_t, 5 * RCtime);

   dss::Step step;
   step.config({1, {}, {0, 3000, 0.1}});
   dss::Summator sum;
   sum.config({2, {1, -4}, {}});
   dss::OnOff onoff;
   onoff.config({3, {2}, {0, 4000, 0}});
   dss::FirstOrder RCcircuit;
   RCcircuit.config({4, {3}, {RCtime, 2500.0}});

   double setpoint{0.0};
   double error{0.0};
   double control{0.0};

   std::ofstream simdata;
   if (argc == 2) {
      simdata.open(argv[1]);
   }

   dss::SimBlock::setExeSequence();
   dss::SimBlock::initSimBlocks();

   do {
      std::cout << "  t = " << std::setw(5) << dss::SimBlock::sim_time.t
                << "  Setpoint = " << std::setw(5) << step.output()
                << "  Control = " << std::setw(5) << onoff.output()
                << "  Measured Value = " << std::setw(8) << RCcircuit.output()
                << std::endl;

      if (argc == 2) {
         simdata << std::setw(4) << dss::SimBlock::sim_time.t << " "
                 << step.output() << " " << onoff.output() << " "
                 << RCcircuit.output() << std::endl;
      }
   } while (dss::SimTime::simulation_on());

   simdata.close();

   return 0;
}
