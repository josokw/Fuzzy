
#include "AppInfo.h"
#include "DySySim.h"
#include "LibInfoDySySim.h"
#include "SimBlockFactory.h"
#include "SimContext.h"

#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace dss = dysysim;

int main(int argc, char *argv[])
{
   std::cout << "-- " APPNAME_VERSION " "
             << "-- uses " + dss::libName + " " << dss::libVersion << "\n\n";

   try {
      dss::SimContext ctx;
      dss::SimBlockFactory sbf(ctx);
      sbf.init();
      const double delta_t{0.005};
      const double RCtime{0.5};
      ctx.sim_time.set(delta_t, 5 * RCtime);

      sbf.configCheck("STP", {1, {}, {0, 3000, 0.1}});
      sbf.configCheck("SUM", {2, {1, -4}, {}});
      sbf.configCheck("ONOFF", {3, {2}, {0, 4000, 0}});
      sbf.configCheck("FIO", {4, {3}, {RCtime, 2500.0}});

      std::ofstream simdata;
      if (argc == 2) {
         simdata.open(argv[1]);
      }

      ctx.setExeSequence();
      ctx.initSimBlocks();
      do {
         ctx.exeSimBlocks();
         std::cout << std::setw(5) << ctx.time() << " "
                   << std::setw(5) << ctx.getSimBlock(1)->output() << " "
                   << std::setw(5) << ctx.getSimBlock(3)->output() << " "
                   << std::setw(8) << ctx.getSimBlock(4)->output()
                   << std::endl;

         if (argc == 2) {
            simdata << std::setw(4) << ctx.time() << " "
                    << std::setw(5) << ctx.getSimBlock(1)->output() << " "
                    << std::setw(5) << ctx.getSimBlock(2)->output() << " "
                    << ctx.getSimBlock(4)->output() << std::endl;
         }
      } while (ctx.sim_time.simulation_is_on());

      simdata.close();
   }
   catch (std::exception &e) {
      std::cerr << "Exception: " << e.what() << "\n";
   }

   return 0;
}
