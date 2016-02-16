#include "AppInfo.h"
#include "Connecting.h"
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
    dss::Time time{1, Tsimulation};
    dss::Step STEP{2, 0, 2048, 0 /*stepTime*/};
    dss::Summator sum{3};
    FuzzyController fuzzyC;
    dss::ZeroOrderHold zoh{4, 1};
    RCcircuit RC{5, RCtime};

    double setpoint{0.0};
    double error{0.0};
    double control{0.0};

    sum >> zoh;

    for(int tn = 0; tn < 600; ++tn) {
        setpoint = STEP.output();
        sum.input(setpoint, -RC.output());
        //sum.input(dss::SimBlock::getOutputSimBlock(2), -RC.output());
        error = sum.output();
        control = fuzzyC.inferControl(error);
        zoh.input(control);
        cout << "ZOH = " << int(zoh.output()) << endl;
        RC.input(zoh.output());

        cout << "t = " << setw(5) << time.output()
             << "  Setpoint = " << setw(6) << setpoint
             << "  Control = " << setw(6) << control
             << "  Measured Value = " << setw(10)
             << RC.output() << endl;

        time.next();
        getchar();
    }

    return 0;
}
