#include "InputFuzzySet.h"
#include <iostream>

std::ostream& InputFuzzySet::write(std::ostream &os) const {
  return os << _name << " input = " << _input << " mbs = " << _mbs;
}
