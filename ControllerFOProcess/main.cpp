#include "AppInfo.h"
#include "RCcircuit.h"
#include "FuzzyController.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "-- " APPNAME_VERSION " " << string(50, '-') << endl << endl;
    const double Tsample{0.1};
    const double Tsimulation{Tsample / 10};
    const double RCtime{0.2};
    FuzzyController controller;
    Step STEP{0};
    RCcircuit RC{Tsimulation, 0, RCtime};
    double setpoint{0.0};
    double error{0.0};
    double output{0.0};

    for(int tn = 0; tn < 1000; ++tn) {
        setpoint = STEP.output(tn) * 2000.0;
        error = setpoint - RC.output();
        output = controller.inferControl(error);
        RC.input(output);

        cout << "t = " << tn * Tsimulation << " input = " << setpoint
             << " output = " << RC.output() << endl;
        //getchar();
    }

    return 0;
}
