#include "AppInfo.h"
#include "DySySim.h"
#include "FuzzyController.h"
#include "LibInfoDySySim.h"
#include "SimBlockFactory.h"
#include "SimContext.h"

#include <exception>
#include <iomanip>
#include <iostream>

namespace dss = dysysim;

/// \todo  Under construction ....
int main(int argc, char *argv[])
{
   std::cout << "-- " APPNAME_VERSION " "
             << "-- uses " + dss::libName + " " << dss::libVersion << "\n\n";

   try {
      dss::SimContext ctx;
      dss::SimBlockFactory sbf(ctx);
      sbf.init();

      FuzzyController fuzzyController;
      auto pFuzzyC = std::make_shared<dss::Function<double>>();
      pFuzzyC->setFunction([&fuzzyController](double in) {
         return fuzzyController.inferControl(in);
      });
      sbf.add("FUZZYC", pFuzzyC);

      const double RCtime{0.47};
      ctx.sim_time.set(0.05, 10.0);

      sbf.configCheck("STP", {1, {}, {0.5, 1, 0.1}});
      sbf.configCheck("SUM", {2, {1, -4}, {}});
      sbf.configCheck("FUZZYC", {3, {2}, {}});
      sbf.configCheck("FIO", {4, {3}, {RCtime, 0.0}});

      std::ofstream simdata;
      if (argc == 2) {
         simdata.open(argv[1]);
      }

      ctx.setExeSequence();
      ctx.initSimBlocks();
      do {
         ctx.exeSimBlocks();
         std::cout << "t = " << std::setw(6) << std::setprecision(1)
                   << ctx.time()
                   << "  Setpoint = " << std::setw(6) << ctx.getSimBlock(1)->output()
                   << "  Control = " << std::setw(6) << ctx.getSimBlock(3)->output()
                   << "  Measured Value = " << std::setw(10) << ctx.getSimBlock(4)->output()
                   << std::endl;
         if (argc == 2) {
            simdata << ctx.time() << " " << ctx.getSimBlock(1)->output() << " "
                    << ctx.getSimBlock(3)->output() << " " << ctx.getSimBlock(4)->output() << std::endl;
         }
      } while (ctx.sim_time.simulation_is_on());

      simdata.close();
   }
   catch (std::exception &e) {
      std::cerr << "Exception: " << e.what() << "\n";
   }

   return 0;
}
