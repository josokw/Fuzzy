#include "TippingFIS.h"
#include "FuzzyLogic.h"

int TippingFIS::inferTip(int food, int service, DEFUZ defuzFunction) {
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
  switch (defuzFunction) {
     case DEFUZ::MoM:
        return defuzMeanOfMaximum<3>(fuzzyTip);
     case DEFUZ::FoM:
        return defuzFirstOfMaxima<3>(fuzzyTip);
     case DEFUZ::LoM:
        return defuzLastOfMaxima<3>(fuzzyTip);
     case DEFUZ::WA:
        return defuzWeightedAverage<3>(fuzzyTip);
  }
  return 0;
}
