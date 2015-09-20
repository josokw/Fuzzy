#include "InputFuzzySet.h"
#include <iostream>

void InputFuzzySet::write(std::ostream &os) const {
  os << _name << " input = " << _input << " mbs = " << _mbs;
}
