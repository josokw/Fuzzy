#include "TippingFIS.h"
#include "FuzzyLogic.h"
#include "OutputFuzzySet.h"

std::ostream &operator<<(std::ostream &os, const TippingFIS &lhs)
{
   os << lhs.poor << "\n" << lhs.good << "\n" << lhs.great << "\n";
   os << lhs.rancid << "\n" << lhs.delicious << "\n";
   os << lhs.cheap << "\n" << lhs.average << "\n" << lhs.generous << "\n";

   return os;
}

int TippingFIS::inferTip(int food, int service, DEFUZ defuzFunction)
{
   // Set inputs
   for (auto &fs : fuzzyService) {
      fs->setInput(service);
   }
   for (auto &fs : fuzzyFood) {
      fs->setInput(food);
   }

   cheap.clearMbs();
   // IF service is poor OR food is rancid THEN tip is cheap
   cheap = (poor or rancid) * 1.0;

   average.clearMbs();
   // IF service is good THEN tip is average
   average = good * 1.0;

   generous.clearMbs();
   // IF service is excellent OR food is delicious THEN tip is generous
   // with 0.5
   generous = (great or delicious) * 0.5;
   //  IF service is excellent AND food is delicious THEN tip is generous
   //  with 1.0
   generous = (great and delicious) * 1.0;

   // std::cout << *this << std::endl;

   // Defuzzification
   switch (defuzFunction) {
      case DEFUZ::MoM:
         return defuzMeanOfMaximum(fuzzyTip);
      case DEFUZ::FoM:
         return defuzFirstOfMaxima(fuzzyTip);
      case DEFUZ::LoM:
         return defuzLastOfMaxima(fuzzyTip);
      case DEFUZ::WA:
         return defuzWeightedAverage(fuzzyTip);
      case DEFUZ::CoS:
         return defuzCenterOfSums(fuzzyTip);
   }

   return 0;
}
