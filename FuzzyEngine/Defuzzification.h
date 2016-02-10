#ifndef DEFUZZIFICATION
#define DEFUZZIFICATION

#include "OutputFuzzySet.h"
#include <array>
#include <cmath>
#include <iostream>

namespace {

const double EPSILON = 1e-4;

inline constexpr
bool equals(double d1, double d2) {
   return std::fabs(d1 - d2) < EPSILON;
}

template<int N>
const OutputFuzzySet* findHighestMbsSet(
      const std::array<OutputFuzzySet*, N>& fs) {
   double highestMBS = 0;
   int highestIndex = 0;
   int index = 0;
   for(auto& f : fs) {
      if(f->getMbs() > highestMBS) {
         highestMBS = f->getMbs();
         highestIndex = index;
      }
      ++index;
   }
   return fs[highestIndex];
}
}

enum class DEFUZ {MoM, FoM, LoM, WA};

template<int N>
double defuzMeanOfMaximum(const std::array<OutputFuzzySet*, N>& fs) {
   return findHighestMbsSet<N>(fs)->meanOfMaximum();
}

template<int N>
double defuzFirstOfMaxima(const std::array<OutputFuzzySet*, N>& fs) {
   return findHighestMbsSet<N>(fs)->firstOfMaxima();
}

template<int N>
double defuzLastOfMaxima(const std::array<OutputFuzzySet*, N>& fs) {
   return findHighestMbsSet<N>(fs)->lastOfMaxima();
}

template<int N>
double defuzWeightedAverage(const std::array<OutputFuzzySet*, N>& fs) {
   double numerator = 0;
   double denomenator = 0;
   for(auto& f : fs) {
      numerator += f->getMbs() * f->meanOfMaximum();
      denomenator += f->getMbs();
   }
   return denomenator != 0.0 ? numerator / denomenator : 0;
}

#endif // DEFUZZIFICATION
