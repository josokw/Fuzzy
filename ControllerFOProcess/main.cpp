#include "AppInfo.h"
#include "RCcircuit.h"
#include "FuzzyController.h"
#include "LibInfoDySySim.h"
#include <iomanip>
#include <iostream>

using namespace std;

namespace dss = dysysim;

int main()
{
    cout << "-- " APPNAME_VERSION " " << string(50, '-') << endl
         << "-- uses " + dss::libName + " " << dss::libVersion << endl << endl;
    const double Tsample{0.005};
    const double Tsimulation{Tsample};
//  const double stepTime = 10 * Tsimulation;
    const double RCtime{0.2};
    // Model
    dss::Time time{Tsimulation};
    dss::Step STEP{0, 2048, 0 /*stepTime*/};
    dss::Summator sum;
    FuzzyController fuzzyC;
    dss::ZeroOrderHold zoh{1};
    RCcircuit RC{RCtime};

    double setpoint{0.0};
    double error{0.0};
    double control{0.0};

    for(int tn = 0; tn < 600; ++tn) {
        setpoint = STEP.output();
        sum.input(setpoint, -RC.output());
        error = sum.output();
        control = fuzzyC.inferControl(error);
        zoh.input(control);
        cout << "ZOH = " << int(zoh.output()) << endl;
        RC.input(zoh.output());

        cout << "t = " << setw(5) << time.output()
             << "  Setpoint = " << setw(6) << setpoint
             << "  Measured Value = " << setw(10)
             << RC.output() << endl;

        time.next();
        getchar();
    }

    return 0;
}
