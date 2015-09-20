#ifndef DEFUZZIFICATION
#define DEFUZZIFICATION

#include "OutputFuzzySetTriangular.h"
#include <array>
#include <iostream>

template<int N>
double defuzMeanOfMaximumTriangular(
    const std::array<OutputFuzzySetTriangular*, N>& fs)
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

  return fs[highestIndex]->_t[1];
}

#endif // DEFUZZIFICATION

