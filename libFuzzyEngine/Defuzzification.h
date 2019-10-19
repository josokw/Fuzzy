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

enum class DEFUZ { MoM, FoM, LoM, WA, CoS };

/// Maxima method: MoM.
inline double defuzMeanOfMaximum(const std::vector<OutputFuzzySet *> &fs)
{
   return findHighestMbsSet(fs)->meanOfMaximum();
}

/// Maxima method: FoM.
inline double defuzFirstOfMaxima(const std::vector<OutputFuzzySet *> &fs)
{
   return findHighestMbsSet(fs)->firstOfMaxima();
}

/// Maxima method: LoM.
inline double defuzLastOfMaxima(const std::vector<OutputFuzzySet *> &fs)
{
   return findHighestMbsSet(fs)->lastOfMaxima();
}

/// Also known as Sugeno defuzzyfication, this method can only be used for
/// symmetrical memebrship functions.
inline double defuzWeightedAverage(const std::vector<OutputFuzzySet *> &fs)
{
   double crisp{0.0};
   double numerator{0.0};
   double denomenator{0.0};

   for (auto &f : fs) {
      numerator += f->getMbs() * f->meanOfMaximum();
      denomenator += f->getMbs();
   }
   crisp = denomenator != 0.0 ? numerator / denomenator : 0;

   return crisp;
}

/// A centroid method: CoS.
inline double defuzCenterOfSums(const std::vector<OutputFuzzySet *> &vfs)
{
   double crisp{0};
   double numerator{0.0};
   double denomenator{0.0};

   for (auto &fs : vfs) {
      auto [minr, maxr] = fs->range();
      auto midpoint{(minr + maxr) / 2.0};
      auto ar{fs->area()};
      numerator += ar * midpoint;
      denomenator += ar;
   }

   crisp = numerator / denomenator;

   return crisp;
}

#endif // DEFUZZIFICATION
