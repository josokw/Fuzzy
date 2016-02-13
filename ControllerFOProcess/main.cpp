#include "AppInfo.h"
#include "RCcircuit.h"
#include "FuzzyController.h"
#include <iomanip>
#include <iostream>

using namespace std;

namespace dss = dysysim;

int main()
{
    cout << "-- " APPNAME_VERSION " " << string(50, '-') << endl << endl;
    const double Tsample{0.1};
    const double Tsimulation{Tsample / 10};
    const double stepTime = 10 * Tsimulation;
    const double RCtime{0.2};
    // Model
    dss::Time time{Tsimulation};
    dss::Step STEP{0, 2000.0, stepTime};
    FuzzyController fuzzyC;
    dss::ZeroOrderHold zoh{5};
    RCcircuit RC{Tsample, 0, RCtime};

    double setpoint{0.0};
    double error{0.0};
    double output{0.0};

    for(int tn = 0; tn < 400; ++tn) {
        setpoint = STEP.output();
        error = setpoint - RC.output();
        output = fuzzyC.inferControl(error);
        zoh.input(error);
        cout << "ZOH = " << zoh.output() << endl;
        RC.input(zoh.output());

        cout << "t = " << setw(5) << time.output()
             << "  input = " << setw(6) << setpoint
             << "  output = " << setw(10) << fixed << setprecision(2)
             << RC.output() << endl;

        time.next();
        getchar();
    }

    return 0;
}
