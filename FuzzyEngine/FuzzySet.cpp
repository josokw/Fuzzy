#include "FuzzySet.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const FuzzySet& fs)
{
  return fs.write(os);
}
