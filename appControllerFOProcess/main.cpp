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
   std::cout << "-- " APPNAME_VERSION " "
             << "-- uses " + dss::libName + " " << dss::libVersion << "\n\n";

   const double Tsample{0.005}; // 5 msec
   double Tsimulation{Tsample};
   //  const double stepTime = 10 * Tsimulation;
   const double RCtime{0.47}; // tau 0.47 sec

   // Model
   dss::Time time;
   time.config({1, {}, {Tsimulation}});
   dss::Step step;
   step.config({2, {}, {0, 2048, 0}});
   dss::Summator sum;
   sum.config({3, {}, {}});

   FuzzyController fuzzyController;
   dss::Function<double> fuzzyC;
   fuzzyC.setFunction([&fuzzyController](double in) {
      return fuzzyController.inferControl(in);
   });
   fuzzyC.config({4, {}, {}});

   dss::FirstOrder RCcircuit;
   RCcircuit.config({5, {}, {RCtime}});

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
