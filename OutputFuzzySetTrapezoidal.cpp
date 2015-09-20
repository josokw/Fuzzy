#include "OutputFuzzySetTrapezoidal.h"
#include <iostream>

OutputFuzzySetTrapezoidal::OutputFuzzySetTrapezoidal(const std::string& name,
                                                   double t1, double t2,
                                                   double t3, double t4)
  : OutputFuzzySet{name}
  , _t{t1, t2, t3, t4}
{}
