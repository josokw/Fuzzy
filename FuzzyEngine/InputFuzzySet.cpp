#include "InputFuzzySet.h"
#include "OutputFuzzySet.h"
#include <iostream>

OutputFuzzySet operator*(const InputFuzzySet& lhs, double rhs) {
  OutputFuzzySet result;
  result.setMbs(lhs._mbs * rhs);
  return result;
}

std::ostream& InputFuzzySet::write(std::ostream &os) const {
  return os << _name << " input = " << _input << " mbs = " << _mbs;
}
