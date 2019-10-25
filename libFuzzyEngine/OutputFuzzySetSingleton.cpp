#include "OutputFuzzySetSingleton.h"

OutputFuzzySetSingleton::OutputFuzzySetSingleton(const std::string &name,
                                                 double t0)
   : OutputFuzzySet{name}
   , _t{t0}
{
}

OutputFuzzySetSingleton &OutputFuzzySetSingleton::
operator=(const OutputFuzzySet &other)
{
   setMbs(other.getMbs());
   return *this;
}

double OutputFuzzySetSingleton::firstOfMaxima() const
{
   return mbs_;
}

double OutputFuzzySetSingleton::lastOfMaxima() const
{
   return mbs_;
}

double OutputFuzzySetSingleton::meanOfMaximum() const
{
   return mbs_;
}

std::ostream &OutputFuzzySetSingleton::write(std::ostream &os) const
{
   return OutputFuzzySet::write(os) << " (" << _t[0] << ") mbs = " << mbs_;
}
