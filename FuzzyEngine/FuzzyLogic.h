#ifndef FUZZYLOGIC
#define FUZZYLOGIC

#include "FuzzySet.h"
#include "OutputFuzzySet.h"

inline OutputFuzzySet operator||(const FuzzySet &lhs, const FuzzySet &rhs)
{
   OutputFuzzySet result;
   result._mbs = std::max(lhs._mbs, rhs._mbs);
   return result;
}

inline OutputFuzzySet operator&&(const FuzzySet &lhs, const FuzzySet &rhs)
{
   OutputFuzzySet result;
   result._mbs = std::min(lhs._mbs, rhs._mbs);
   return result;
}

inline OutputFuzzySet operator!(const FuzzySet &fs)
{
   OutputFuzzySet result;
   result._mbs = 1 - fs._mbs;
   return result;
}

#endif // FUZZYLOGIC
