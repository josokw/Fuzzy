#include "AppInfo.h"
#include "DySySim.h"
#include "FuzzyController.h"
#include "LibInfoDySySim.h"
#include "SimBlockFactory.h"

#include <exception>
#include <iomanip>
#include <iostream>

namespace dss = dysysim;

inline double getOutput(int id)
{
   return dss::SimBlock::getSimBlock(id)->output();
}

/// \todo  Under construction ....
int main(int argc, char *argv[])
{
   std::cout << "-- " APPNAME_VERSION " "
             << "-- uses " + dss::libName + " " << dss::libVersion << "\n\n";

   try {
      dss::SimBlockFactory sbf;
      sbf.init();

      FuzzyController fuzzyController;
      auto pFuzzyC = std::make_shared<dss::Function<double>>();
      pFuzzyC->setFunction([&fuzzyController](double in) {
         return fuzzyController.inferControl(in);
      });
      sbf.add("FUZZYC", pFuzzyC);

      const double RCtime{0.47};
      dss::SimTime::set(0.05, 10.0);

      sbf.configCheck("STP", {1, {}, {0.5, 1, 0.1}});
      sbf.configCheck("SUM", {2, {1, -4}, {}});
      sbf.configCheck("FUZZYC", {3, {2}, {}});
      sbf.configCheck("FIO", {4, {3}, {RCtime, 0.0}});

      std::ofstream simdata;
      if (argc == 2) {
         simdata.open(argv[1]);
      }

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      do {
         std::cout << "t = " << std::setw(6) << std::setprecision(1)
                   << dss::SimBlock::sim_time.t
                   << "  Setpoint = " << std::setw(6) << getOutput(1)
                   << "  Control = " << std::setw(6) << getOutput(3)
                   << "  Measured Value = " << std::setw(10) << getOutput(4)
                   << std::endl;
         if (argc == 2) {
            simdata << dss::SimBlock::sim_time.t << " " << getOutput(1) << " "
                    << getOutput(3) << " " << getOutput(4) << std::endl;
         }
      } while (dss::SimTime::simulation_on());

      simdata.close();
   }
   catch (std::exception &e) {
      std::cerr << "Exception: " << e.what() << "\n";
   }

   return 0;
}
