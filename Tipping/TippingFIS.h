#ifndef TIPPINGFIS_H
#define TIPPINGFIS_H

#include "Defuzzification.h"
#include "InputFuzzySetTrapezoidal.h"
#include "InputFuzzySetTriangular.h"
#include "OutputFuzzySetTriangular.h"
#include <array>

/// Tipping Fuzzy Inference (Expert) System
class TippingFIS {
   friend std::ostream &operator<<(std::ostream &os, const TippingFIS &lhs);

public:
   TippingFIS() = default;
   ~TippingFIS() = default;
   int inferTip(int food, int service, DEFUZ defuzFunction);

private:
   // Linguistic variable: Service
   InputFuzzySetTriangular poor{ "Service = poor", 0, 2.5, 5 };
   InputFuzzySetTriangular good{ "Service = good", 2.5, 5, 7.5 };
   InputFuzzySetTriangular great{ "Service = great", 5, 7.5, 10 };

   // Liguistic variable: Food
   InputFuzzySetTrapezoidal rancid{ "Food = rancid", 0, 0, 1.5, 4 };
   InputFuzzySetTrapezoidal delicious{ "Food = delicious", 6, 8.5, 10, 10 };

   // Linguistic variable: Tip
   OutputFuzzySetTriangular cheap{ "Tip = cheap", 0, 5, 10 };
   OutputFuzzySetTriangular average{ "Tip = average", 10, 15, 20 };
   OutputFuzzySetTriangular generous{ "Tip = generous", 20, 25, 30 };

   // Polymorfic arrays containing pointers (base class) to fuzzy sets
   std::array<InputFuzzySet *, 3> fuzzyService = { { &poor, &good, &great } };
   std::array<InputFuzzySet *, 2> fuzzyFood = { { &rancid, &delicious } };
   std::array<OutputFuzzySet *, 3> fuzzyTip = { { &cheap, &average, &generous } };
};

#endif // TIPPINGFIS_H
