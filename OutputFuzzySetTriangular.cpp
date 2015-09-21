#include "OutputFuzzySetTriangular.h"
#include <iostream>

OutputFuzzySetTriangular::OutputFuzzySetTriangular(const std::string& name,
                                                   double t1, double t2,
                                                   double t3)
  : OutputFuzzySet{name}
  , _t{t1, t2, t3}
{}

OutputFuzzySetTriangular&
OutputFuzzySetTriangular::operator=(const OutputFuzzySet& other){
  _mbs = other.getMbs();
  return *this;
}
