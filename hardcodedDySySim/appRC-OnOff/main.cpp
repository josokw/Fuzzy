#include "AppInfo.h"
#include "DySySimProgram.h"
#include "LibInfoDySySim.h"

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
      dss::DySySimProgram prog;
      const double RCtime{0.5};
      prog.setSimTime(0.005, 5 * RCtime);

      prog.configureBlock("STP", {1, {}, {0, 3000, 0.1}});
      prog.configureBlock("SUM", {2, {1, -4}, {}});
      prog.configureBlock("ONOFF", {3, {2}, {0, 4000, 0}});
      prog.configureBlock("FIO", {4, {3}, {RCtime, 2500.0}});

      std::ofstream simdata;
      if (argc == 2) {
         simdata.open(argv[1]);
      }

      prog.setStepCallback([&, argc](dss::SimContext &ctx) {
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
      });

      auto errors = prog.run();
      if (!errors.empty()) {
         for (const auto &err : errors) {
            std::cerr << "Error: " << err.message() << "\n";
         }
      }

      simdata.close();
   }
   catch (std::exception &e) {
      std::cerr << "Exception: " << e.what() << "\n";
   }

   return 0;
}
