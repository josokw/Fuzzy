#include "InputFuzzySet.h"
#include "OutputFuzzySet.h"
#include <iostream>

OutputFuzzySet operator*(const InputFuzzySet &lhs, double rhs)
{
   OutputFuzzySet result;
   result.setMbs(lhs.mbs_ * rhs);
   return result;
}

std::ostream &InputFuzzySet::write(std::ostream &os) const
{
   return os << name_ << " input = " << input_ << " mbs = " << mbs_;
}
