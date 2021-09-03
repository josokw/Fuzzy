#include "AppInfo.h"
#include "DySySim.h"
#include "FuzzyController.h"
#include "LibInfoDySySim.h"

#include <iomanip>
#include <iostream>

namespace dss = dysysim;

/// Under construction ....
int main(int argc, char *argv[])
{
   std::cout << "-- " APPNAME_VERSION " "
             << "-- uses " + dss::libName + " " << dss::libVersion << "\n\n";

   const double RCtime{0.47}; // FOP tau 0.47 sec
   dss::SimTime::set(0.005, 20.0);

   // Model
   dss::Step step;
   step.config({1, {}, {0, 2055, 0.01}});
   dss::Summator sum;
   sum.config({2, {1, -4}, {}});

   FuzzyController fuzzyController;
   dss::Function<double> fuzzyC;
   fuzzyC.setFunction([&fuzzyController](double in) {
      return fuzzyController.inferControl(in);
   });
   fuzzyC.config({3, {2}, {}});

   dss::FirstOrder RCcircuit;
   RCcircuit.config({4, {3}, {RCtime, 0}});

   std::ofstream simdata;
   if (argc == 2) {
      simdata.open(argv[1]);
   }

   dss::SimBlock::setExeSequence();
   dss::SimBlock::initSimBlocks();
   do {
      std::cout << "t = " << std::setw(5) << dss::SimBlock::sim_time.t
                << "  Setpoint = " << std::setw(6) << step.output()
                << "  Control = " << std::setw(6) << fuzzyC.output()
                << "  Measured Value = " << std::setw(10) << RCcircuit.output()
                << std::endl;
      if (argc == 2) {
         simdata << dss::SimBlock::sim_time.t << " " << step.output() << " "
                 << fuzzyC.output() << " " << RCcircuit.output() << std::endl;
      }
   } while (dss::SimTime::simulation_on());

   simdata.close();

   return 0;
}
