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
   setMbs(other.getMbs());
   return *this;
}

double OutputFuzzySetTriangular::firstOfMaxima() const
{
   return _t[0] + mbs_ * (_t[1] - _t[0]);
}

double OutputFuzzySetTriangular::lastOfMaxima() const
{
   return _t[2] - mbs_ * (_t[2] - _t[1]);
}

double OutputFuzzySetTriangular::meanOfMaximum() const
{
   return (firstOfMaxima() + lastOfMaxima()) / 2.0;
}

double OutputFuzzySetTriangular::area() const
{
   return (_t[2] - _t[0]) * mbs_;
}

std::ostream &OutputFuzzySetTriangular::write(std::ostream &os) const
{
   return OutputFuzzySet::write(os) << " (" << _t[0] << ", " << _t[1] << ", "
                                    << _t[2] << ") mbs = " << mbs_;
}
