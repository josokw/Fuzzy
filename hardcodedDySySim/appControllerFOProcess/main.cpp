#include "AppInfo.h"
#include "DySySim.h"
#include "DySySimProgram.h"
#include "FuzzyController.h"
#include "LibInfoDySySim.h"

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
      dss::DySySimProgram prog;

      FuzzyController fuzzyController;
      auto pFuzzyC = std::make_shared<dss::Function<double>>();
      pFuzzyC->setFunction([&fuzzyController](double in) {
         return fuzzyController.inferControl(in);
      });
      prog.addBlock("FUZZYC", pFuzzyC);

      const double RCtime{0.47};
      prog.setSimTime(0.05, 10.0);

      prog.configureBlock("STP", {1, {}, {0.5, 1, 0.1}});
      prog.configureBlock("SUM", {2, {1, -4}, {}});
      prog.configureBlock("FUZZYC", {3, {2}, {}});
      prog.configureBlock("FIO", {4, {3}, {RCtime, 0.0}});

      std::ofstream simdata;
      if (argc == 2) {
         simdata.open(argv[1]);
      }

      prog.setStepCallback([&, argc](dss::SimContext &ctx) {
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
