#include "AppInfo.h"
#include "FuzzyLogic.h"
#include "TippingFIS.h"

#include <array>
#include <iomanip>
#include <iostream>
#include <string>

void doTippingFIS(std::ostream &os, TippingFIS &tfis, DEFUZ defuzzification,
                  LogicModel lm = LogicModel::Zadeh);

int main()
{
   std::cout << "-- " APPNAME_VERSION << " " << std::string(50, '-')
             << std::endl
             << std::endl;

   TippingFIS tippingFIS;

   std::cout << tippingFIS << std::endl;

   std::cout << "-- Defuzzification: Mean of Maximum" << std::endl << std::endl;
   doTippingFIS(std::cout, tippingFIS, DEFUZ::MoM);

   std::cout << "-- Defuzzification: First of Maxima" << std::endl << std::endl;
   doTippingFIS(std::cout, tippingFIS, DEFUZ::FoM);

   std::cout << "-- Defuzzification: Last of Maxima" << std::endl << std::endl;
   doTippingFIS(std::cout, tippingFIS, DEFUZ::LoM);

   std::cout << "-- Defuzzification: Weighted Average" << std::endl
             << std::endl;
   doTippingFIS(std::cout, tippingFIS, DEFUZ::WA);

   std::cout << "-- Defuzzification: Center of Sums, "
                "logic model: Zadeh\n\n";
   doTippingFIS(std::cout, tippingFIS, DEFUZ::CoS, LogicModel::Zadeh);

   std::cout << "-- Defuzzification: Center of Sums, "
                "logic model: Lukasiewicz\n\n";
   doTippingFIS(std::cout, tippingFIS, DEFUZ::CoS, LogicModel::Lukasiewicz);

   return 0;
}

void doTippingFIS(std::ostream &os, TippingFIS &tfis, DEFUZ defuzzification,
                  LogicModel logicmodel)
{
   const int FOOD_MAX = 11;

   os << " service" << std::endl << std::endl;
   for (int service = 10; service >= 0; --service) {
      os << std::setw(8) << service << "  ";
      for (int food = 0; food < FOOD_MAX; ++food) {
         os << std::setw(5)
            << tfis.inferTip(food, service, defuzzification, logicmodel);
      }
      os << std::endl;
   }
   os << std::endl << "    food  ";
   for (int food = 0; food < FOOD_MAX; ++food) {
      os << std::setw(5) << food;
   }
   os << std::endl << std::endl;
}
