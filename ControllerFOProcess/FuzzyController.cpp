#include "Defuzzification.h"
#include "FuzzyController.h"

FuzzyController::FuzzyController() {
   // Rules
   control_negL = error_negl;
   control_neg = error_neg;
   control_no = error_no;
   control_pos = error_pos;
   control_posL = error_posL;
}

double FuzzyController::inferControl(double error) {
   // Set inputs
   for(auto& ifs: errors){
      ifs->setInput(error);
   }
   // Rules
   control_negL = error_negl;
   control_neg = error_neg;
   control_no = error_no;
   control_pos = error_pos;
   control_posL = error_posL;
   // Defuzzification
   return defuzMeanOfMaximum<5>(controls);
}
