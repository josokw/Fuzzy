#include "TippingFIS.h"
#include "Defuzzification.h"
#include "FuzzyLogic.h"

int TippingFIS::inferTip(int food, int service) {
  // Set inputs
  for(auto& fs : fuzzyService) {
    fs->setInput(service);
  }
  for(auto& fs : fuzzyFood) {
    fs->setInput(food);
  }
  // Rule base
  cheap = (poor or rancid) * 1.0;
  average = good * 1.0;
  generous = (great or delicious) * 1.0;
  // Defuzzification
  return int(defuzMeanOfMaximum<3>(fuzzyTip));
}
