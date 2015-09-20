#ifndef FUZZYLOGIC
#define FUZZYLOGIC

#include "FuzzySet.h"
#include "OutputFuzzySet.h"

inline
OutputFuzzySet operator||(const FuzzySet& lhs, const FuzzySet& rhs) {
  OutputFuzzySet result;
  result._mbs = std::max(lhs.getMbs(), rhs.getMbs());
  return result;
}

inline
OutputFuzzySet operator&&(const FuzzySet& lhs, const FuzzySet& rhs) {
  OutputFuzzySet result;
  result._mbs = std::min(lhs.getMbs(), rhs.getMbs());
  return result;
}

inline
OutputFuzzySet operator!(const FuzzySet& fs) {
  OutputFuzzySet result;
  result._mbs = 1 - fs.getMbs();
  return result;
}

#endif // FUZZYLOGIC

