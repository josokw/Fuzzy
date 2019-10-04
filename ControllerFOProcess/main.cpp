#include "AppInfo.h"
#include "Connecting.h"
#include "FuzzyController.h"
#include "LibInfoDySySim.h"
#include "Model.h"

#include <iomanip>
#include <iostream>

namespace dss = dysysim;

int main(int argc, char *argv[])
{
   std::cout << "-- " APPNAME_VERSION " " << std::string(50, '-') << std::endl
             << "-- uses " + dss::libName + " " << dss::libVersion << std::endl
             << std::endl;

   const double Tsample{0.005}; // 5 msec
   const double Tsimulation{Tsample};
   //  const double stepTime = 10 * Tsimulation;
   const double RCtime{0.47}; // tau 0.47 sec

   // Model
   dss::Time time{1, Tsimulation};
   dss::Step step{2, 0, 2048, 0 /*stepTime*/};
   dss::Summator sum{3};
   FuzzyController fuzzyController;
   dss::Function<double> fuzzyC(4, [&fuzzyController](double in) {
      return fuzzyController.inferControl(in);
   });
   dss::FirstOrder RCcircuit{5, RCtime};

   double setpoint{0.0};
   double error{0.0};
   double control{0.0};

   std::ofstream simdata;
   if (argc == 2) {
      simdata.open(argv[1]);
   }

   for (int tn = 0; tn < 1000; ++tn) {
      setpoint = step.output();

      sum.input(setpoint, -RCcircuit.output());
      error = sum.output();

      fuzzyC.input(error);
      control = fuzzyC.output();

      std::cout << "t = " << std::setw(5) << time.output()
                << "  Setpoint = " << std::setw(6) << setpoint
                << "  Control = " << std::setw(6) << control
                << "  Measured Value = " << std::setw(10) << RCcircuit.output()
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
