#include "AppInfo.h"
#include "Connecting.h"
#include "FuzzyController.h"
#include "LibInfoDySySim.h"
#include "Model.h"
#include <iomanip>
#include <iostream>

using namespace std;

namespace dss = dysysim;

int main(int argc, char* argv[])
{
   cout << "-- " APPNAME_VERSION " " << string(50, '-') << endl
        << "-- uses " + dss::libName + " " << dss::libVersion << endl << endl;

   const double Tsample{0.005};  // 5 msec
   const double Tsimulation{Tsample};
   //  const double stepTime = 10 * Tsimulation;
   const double RCtime{0.47}; // tau 0.47 sec
   // Model
   dss::Time time{1, Tsimulation};
   dss::Step step{2, 0, 2048, 0 /*stepTime*/};
   dss::Summator sum{3};
   FuzzyController fuzzyController;
   dss::Function<double> fuzzyC(4,
                                [&fuzzyController](double in){ return fuzzyController.inferControl(in); });
   //dss::ZeroOrderHold zoh{5, 1};
   dss::FirstOrder RCcircuit{10, RCtime};

   //   dss::Model model("Fuzzy controller", 0.05, {});
   //   model.write(cout);
   //   model.simulate(600);

   double setpoint{0.0};
   double error{0.0};
   double control{0.0};

   std::ofstream simdata;
   if (argc == 2) {
      simdata.open(argv[1]);
   }

   for(int tn = 0; tn < 1000; ++tn) {
      step.next();
      setpoint = step.output();
      sum.input(setpoint, -RCcircuit.output());
      error = sum.output();
      fuzzyC.input(error);
      control = fuzzyC.output();
      //zoh.input(control);
      //cout << "ZOH = " << int(zoh.output()) << endl;
      //RCcircuit.input(zoh.output());
      RCcircuit.input(control);

      cout << "t = " << setw(5) << time.output()
           << "  Setpoint = " << setw(6) << setpoint
           << "  Control = " << setw(6) << control
           << "  Measured Value = " << setw(10)
           << RCcircuit.output() << endl;

      if (argc == 2) {
         simdata << setw(4) << time.output() << " "
                 << setpoint << " "
                 << control  << " "
                 << RCcircuit.output() << endl;
      }

      time.next();
      if (argc == 1) {
         getchar();
      }
   }
   simdata.close();

   return 0;
}
