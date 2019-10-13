#include "OutputFuzzySetTriangular.h"

OutputFuzzySetTriangular::OutputFuzzySetTriangular(const std::string &name,
                                                   double t0, double t1,
                                                   double t2)
   : OutputFuzzySet{name}
   , _t{t0, t1, t2}
{
}

OutputFuzzySetTriangular &OutputFuzzySetTriangular::
operator=(const OutputFuzzySet &other)
{
   _mbs = other.getMbs();
   return *this;
}

double OutputFuzzySetTriangular::firstOfMaxima() const
{
   return _t[0] + _mbs * (_t[1] - _t[0]);
}

double OutputFuzzySetTriangular::lastOfMaxima() const
{
   return _t[2] - _mbs * (_t[2] - _t[1]);
}

double OutputFuzzySetTriangular::meanOfMaximum() const
{
   return (firstOfMaxima() + lastOfMaxima()) / 2.0;
}