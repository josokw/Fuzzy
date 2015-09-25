#include "OutputFuzzySetTriangular.h"

OutputFuzzySetTriangular::OutputFuzzySetTriangular(const std::string& name,
                                                   double t0, double t1,
                                                   double t2)
  : OutputFuzzySet{name}
  , _t{t0, t1, t2}
{}

OutputFuzzySetTriangular&
OutputFuzzySetTriangular::operator=(const OutputFuzzySet& other){
  _mbs = other.getMbs();
  return *this;
}
