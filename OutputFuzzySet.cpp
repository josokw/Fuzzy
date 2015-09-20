#include "OutputFuzzySet.h"
#include <iostream>

void OutputFuzzySet::write(std::ostream &os) const {
  os << _name << " mbs = " << _mbs;
}
