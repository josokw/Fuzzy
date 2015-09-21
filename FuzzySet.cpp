#include "FuzzySet.h"
#include "OutputFuzzySet.h"
#include "FuzzyLogic.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const FuzzySet& fs)
{
  fs.write(os);
  return os;
}
