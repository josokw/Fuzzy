#ifndef FUZZYLOGIC
#define FUZZYLOGIC

#include "FuzzySet.h"
#include "OutputFuzzySet.h"

inline OutputFuzzySet operator||(const FuzzySet &lhs, const FuzzySet &rhs)
{
   OutputFuzzySet result;
   result.mbs_ = std::max(lhs.mbs_, rhs.mbs_);
   return result;
}

inline OutputFuzzySet operator&&(const FuzzySet &lhs, const FuzzySet &rhs)
{
   OutputFuzzySet result;
   result.mbs_ = std::min(lhs.mbs_, rhs.mbs_);
   return result;
}

inline OutputFuzzySet operator!(const FuzzySet &fs)
{
   OutputFuzzySet result;
   result.mbs_ = 1 - fs.mbs_;
   return result;
}

#endif // FUZZYLOGIC
