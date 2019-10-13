#include "InputFuzzySetTriangular.h"

#include <algorithm>
#include <iostream>

InputFuzzySetTriangular::InputFuzzySetTriangular(const std::string &name,
                                                 double t0, double t1,
                                                 double t2)
   : InputFuzzySet{name}
   , _t{t0, t1, t2}
{
}

double InputFuzzySetTriangular::membership() const
{
   double min1 = std::min((_input - _t[0]) / (_t[1] - _t[0]), 1.0);
   double min2 = std::min((_t[2] - _input) / (_t[2] - _t[1]), 1.0);
   double min3 = std::min(min1, min2);

   _mbs = std::max(min3, 0.0);

   return _mbs;
}
