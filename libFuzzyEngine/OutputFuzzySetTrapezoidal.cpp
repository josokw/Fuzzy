#include "OutputFuzzySetTrapezoidal.h"

OutputFuzzySetTrapezoidal::OutputFuzzySetTrapezoidal(const std::string &name,
                                                     double t0, double t1,
                                                     double t2, double t3)
   : OutputFuzzySet{name}
   , _t{t0, t1, t2, t3}
{
}

OutputFuzzySetTrapezoidal &OutputFuzzySetTrapezoidal::
operator=(const OutputFuzzySet &other)
{
   mbs_ = other.getMbs();
   return *this;
}

double OutputFuzzySetTrapezoidal::firstOfMaxima() const
{
   if (isLeft())
   {
      return _t[0];
   }
   return _t[0] + mbs_ * (_t[1] - _t[0]);
}

double OutputFuzzySetTrapezoidal::lastOfMaxima() const
{
   if (isRight())
   {
      return _t[3];
   }
   return _t[3] - mbs_ * (_t[3] - _t[2]);
}

double OutputFuzzySetTrapezoidal::meanOfMaximum() const
{
   return (firstOfMaxima() + lastOfMaxima()) / 2.0;
}