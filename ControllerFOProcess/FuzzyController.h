#ifndef FUZZYCONTROLLER_H
#define FUZZYCONTROLLER_H

#include "InputFuzzySetTrapezoidal.h"
#include "OutputFuzzySetTriangular.h"
#include <array>

class FuzzyController
{
public:
   FuzzyController();
   double inferControl(double error);
private:
   // Linguistic variable error
   InputFuzzySetTrapezoidal error_negl{"error_negL", -4000, -4000, -2000, -1000};
   InputFuzzySetTrapezoidal error_neg{"error_neg", -2000, -1000, -1000, 0};
   InputFuzzySetTrapezoidal error_no{"error_no", -1000, 0, 0, 1000};
   InputFuzzySetTrapezoidal error_pos{"error_pos", 0, 1000, 1000, 2000};
   InputFuzzySetTrapezoidal error_posL{"error_posL", 1000, 2000, 4000, 4000};
   // Linguistic variable control
   OutputFuzzySetTriangular control_negL{"control_negL", 0, 500, 1500};
   OutputFuzzySetTriangular control_neg{"control_neg", 700, 1500, 2200};
   OutputFuzzySetTriangular control_no{"control_no", 1400, 2000, 2800};
   OutputFuzzySetTriangular control_pos{"control_pos", 2100, 2700, 3400};
   OutputFuzzySetTriangular control_posL{"control_posL", 2700, 3500, 4100};
    // Polymorfic arrays
   std::array<InputFuzzySet*, 5> errors = {{&error_negl, &error_neg, &error_no, &error_pos, &error_posL}};
   std::array<OutputFuzzySet*, 5> controls = {{&control_negL, &control_neg, &control_no, &control_pos, &control_posL}};
};

#endif // FUZZYCONTROLLER_H
