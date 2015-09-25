#include "OutputFuzzySet.h"
#include <iostream>

std::ostream& OutputFuzzySet::write(std::ostream &os) const {
  return os << _name << " mbs = " << _mbs;
}
