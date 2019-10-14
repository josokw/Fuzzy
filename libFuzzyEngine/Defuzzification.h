#ifndef DEFUZZIFICATION
#define DEFUZZIFICATION

#include "OutputFuzzySet.h"

#include <cmath>
#include <iostream>
#include <vector>

namespace {

constexpr double EPSILON = 1e-4;

inline bool equals(double d1, double d2)
{
   return std::fabs(d1 - d2) < EPSILON;
}

const OutputFuzzySet *findHighestMbsSet(const std::vector<OutputFuzzySet *> &fs)
{
   double highestMBS{0};
   int highestIndex{0};
   int index{0};

   for (auto &f : fs) {
      if (f->getMbs() > highestMBS) {
         highestMBS = f->getMbs();
         highestIndex = index;
      }
      ++index;
   }
   return fs[highestIndex];
}
} // namespace

enum class DEFUZ { MoM, FoM, LoM, WA };

inline double defuzMeanOfMaximum(const std::vector<OutputFuzzySet *> &fs)
{
   return findHighestMbsSet(fs)->meanOfMaximum();
}

inline double defuzFirstOfMaxima(const std::vector<OutputFuzzySet *> &fs)
{
   return findHighestMbsSet(fs)->firstOfMaxima();
}

inline double defuzLastOfMaxima(const std::vector<OutputFuzzySet *> &fs)
{
   return findHighestMbsSet(fs)->lastOfMaxima();
}

inline double defuzWeightedAverage(const std::vector<OutputFuzzySet *> &fs)
{
   double numerator = 0;
   double denomenator = 0;

   for (auto &f : fs) {
      numerator += f->getMbs() * f->meanOfMaximum();
      denomenator += f->getMbs();
   }
   return denomenator != 0.0 ? numerator / denomenator : 0;
}

#endif // DEFUZZIFICATION
