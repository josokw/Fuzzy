#include "AppInfo.h"
#include "RCcircuit.h"

#include "Defuzzification.h"
#include "FuzzyLogic.h"
#include "InputFuzzySetTriangular.h"
#include "InputFuzzySetTrapezoidal.h"
#include "OutputFuzzySetTriangular.h"

#include <iostream>

using namespace std;

int main()
{
    InputFuzzySetTrapezoidal
            error_negl{"error_negL", -4000, -4000, -2000, -1000};
    InputFuzzySetTrapezoidal
            error_neg{"error_neg", -2000, -1000, -1000, 0};
    InputFuzzySetTrapezoidal
            error_no{"error_no", -1000, 0, 0, 1000};
    InputFuzzySetTrapezoidal
            error_pos{"error_pos", 0, 1000, 1000, 2000};
    InputFuzzySetTrapezoidal
            error_posL{"error_posL", 1000, 2000, 4000, 4000};

    OutputFuzzySetTriangular
            control_negL{"control_negL", 0, 500, 1500};
    OutputFuzzySetTriangular
            control_neg{"control_neg", 700, 1500, 2200};
    OutputFuzzySetTriangular
            control_no{"control_no", 1400, 2000, 2800};
    OutputFuzzySetTriangular
            control_pos{"control_pos", 2100, 2700, 3400};
    OutputFuzzySetTriangular
            control_posL{"control_posL", 2700, 3500, 4100};

    std::array<InputFuzzySet*, 5> errors{&error_negl, &error_neg,
                                         &error_no,
                                         &error_pos, &error_posL};

    std::array<OutputFuzzySet*, 5> controls{&control_negL, &control_neg,
                                           &control_no,
                                           &control_pos, &control_posL};
    // Rules
    control_negL = error_negl;
    control_neg = error_neg;
    control_no = error_no;
    control_pos = error_pos;
    control_posL = error_posL;

    // RC circuit
    cout << "-- " APPNAME_VERSION " --------------------------" << endl << endl;
    const double Tsample{0.1};
    const double Tsimulation{Tsample / 10};
    const double RCtime{0.2};
    RCcircuit RC{Tsimulation, 0, RCtime};
    double input{0.0};

    // Step function
    for(int i = 0; i < 200; ++i) {
        RC.input(input);
        cout << "t = " << i * Tsimulation << " input = " << input
             << " output = " << RC.output() << endl;
        if (i > 9) {
            input = 1.0;
        }
    }






    return 0;
}
