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
    const double RCtime{0.47};
    // Model
    dss::Time time{1, Tsimulation};
    dss::Step STEP{2, 0, 2048, 0 /*stepTime*/};
    dss::Summator sum{3};

    FuzzyController fuzzyC;
    dss::Function fc(4, [&fuzzyC](double in){ return fuzzyC.inferControl(in); });

    //dss::ZeroOrderHold zoh{5, 1};
    dss::FirstOrder RCcircuit{10, RCtime};

    double setpoint{0.0};
    double error{0.0};
    double control{0.0};

    //sum > zoh > (zoh + sum);

    for(int tn = 0; tn < 600; ++tn) {
        setpoint = STEP.output();
        sum.input(setpoint, -RCcircuit.output());
        //sum.input(dss::SimBlock::getOutputSimBlock(2), -RC.output());
        error = sum.output();
        //control = fuzzyC.inferControl(error);
        fc.input(error);
        control = fc.output();
        //zoh.input(control);
        //cout << "ZOH = " << int(zoh.output()) << endl;
        //RCcircuit.input(zoh.output());
        RCcircuit.input(control);

        cout << "t = " << setw(5) << time.output()
             << "  Setpoint = " << setw(6) << setpoint
             << "  Control = " << setw(6) << control
             << "  Measured Value = " << setw(10)
             << RCcircuit.output() << endl;

        time.next();
        getchar();
    }

    return 0;
}
