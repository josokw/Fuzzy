#ifndef DEFUZZIFICATION
#define DEFUZZIFICATION

#include "OutputFuzzySetTriangular.h"
#include <array>
#include <cmath>
#include <iostream>

const double EPSILON = 1e-4;

inline
bool equals(double d1, double d2) {
  return std::fabs(d1 - d2) < EPSILON;
}

template<int N>
double defuzMeanOfMaximumTriangular(
    const std::array<OutputFuzzySet*, N>& fs)
{
  std::cout << "\n-- Defuzzification by MoM method:\n";
  for(auto& f : fs) {
      std::cout << *f << std::endl;
    }
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

  std::cout << "hIndex " << highestIndex
            << "  hMBS " << highestMBS
            << "  MOM = " << fs[highestIndex]->meanOfMaximum() << std::endl;

  return fs[highestIndex]->meanOfMaximum();
}

#endif // DEFUZZIFICATION

