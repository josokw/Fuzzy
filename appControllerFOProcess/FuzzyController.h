#ifndef FUZZYCONTROLLER_H
#define FUZZYCONTROLLER_H

#include "InputFuzzySetTrapezoidal.h"
#include "OutputFuzzySetTriangular.h"

#include <vector>

class FuzzyController
{
public:
   FuzzyController();
   double inferControl(double error);

private:
   // Linguistic variable error
   InputFuzzySetTrapezoidal error_negl{"error_negL", -4095, -4095, -2048,
                                       -1024};
   InputFuzzySetTrapezoidal error_neg{"error_neg", -2048, -1024, -1024, 0};
   InputFuzzySetTrapezoidal error_no{"error_no", -1024, 0, 0, 1024};
   InputFuzzySetTrapezoidal error_pos{"error_pos", 0, 1024, 1024, 2048};
   InputFuzzySetTrapezoidal error_posL{"error_posL", 1024, 2048, 4095, 4095};

   // Linguistic variable control
   OutputFuzzySetTriangular control_negL{"control_negL", 0, 684.5, 1396};
   OutputFuzzySetTriangular control_neg{"control_neg", 684.5, 1396, 2050};
   OutputFuzzySetTriangular control_no{"control_no", 1396, 2050, 2734};
   OutputFuzzySetTriangular control_pos{"control_pos", 2050, 2734, 3419};
   OutputFuzzySetTriangular control_posL{"control_posL", 2734, 3419, 4095};

   // Polymorfic arrays
   std::vector<InputFuzzySet *> errors{
      {&error_negl, &error_neg, &error_no, &error_pos, &error_posL}};
   std::vector<OutputFuzzySet *> controls{
      {&control_negL, &control_neg, &control_no, &control_pos, &control_posL}};
};

#endif // FUZZYCONTROLLER_H
