#include "OutputFuzzySetTrapezoidal.h"

OutputFuzzySetTrapezoidal::OutputFuzzySetTrapezoidal(const std::string& name,
                                                   double t0, double t1,
                                                   double t2, double t3)
  : OutputFuzzySet{name}
  , _t{t0, t1, t2, t3}
{}

OutputFuzzySetTrapezoidal&
OutputFuzzySetTrapezoidal::operator=(const OutputFuzzySet& other) {
  _mbs = other.getMbs();
  return *this;
}
