#include "OutputFuzzySet.h"
#include <iostream>

OutputFuzzySet operator*(const OutputFuzzySet &lhs, double rhs)
{
   OutputFuzzySet result;
   result.setMbs(lhs.mbs_ * rhs);
   return result;
}

std::ostream &OutputFuzzySet::write(std::ostream &os) const
{
   return os << name_;
}
