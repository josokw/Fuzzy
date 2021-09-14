
#include "AppInfo.h"
#include "DySySim.h"
#include "LibInfoDySySim.h"
#include "SimBlockFactory.h"

#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace dss = dysysim;

inline double getOutput(int id)
{
   return dss::SimBlock::getSimBlock(id)->output();
}

int main(int argc, char *argv[])
{
   std::cout << "-- " APPNAME_VERSION " "
             << "-- uses " + dss::libName + " " << dss::libVersion << "\n\n";

   try {
      dss::SimBlockFactory sbf;
      sbf.init();
      const double delta_t{0.005};
      const double RCtime{0.5};
      dss::SimTime::set(delta_t, 5 * RCtime);
      sbf.configCheck("STP", {1, {}, {0, 3000, 0.1}});
      sbf.configCheck("SUM", {2, {1, -4}, {}});
      sbf.configCheck("ONOFF", {3, {2}, {0, 4000, 0}});
      sbf.configCheck("FIO", {4, {3}, {RCtime, 2500.0}});

      std::ofstream simdata;
      if (argc == 2) {
         simdata.open(argv[1]);
      }

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      do {
         std::cout << "  t = " << std::setw(5) << dss::SimBlock::sim_time.t
                   << "  Setpoint = " << std::setw(5) << getOutput(1)
                   << "  Control = " << std::setw(5) << getOutput(3)
                   << "  Measured Value = " << std::setw(8) << getOutput(4)
                   << std::endl;

         if (argc == 2) {
            simdata << std::setw(4) << dss::SimBlock::sim_time.t << " "
                    << getOutput(1) << " " << getOutput(2) << " "
                    << getOutput(4) << std::endl;
         }
      } while (dss::SimTime::simulation_on());

      simdata.close();
   }
   catch (std::exception &e) {
      std::cerr << "Exception: " << e.what() << "\n";
   }

   return 0;
}
