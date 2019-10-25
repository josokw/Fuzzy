#include "FuzzyLogic.h"
#include "FuzzySet.h"
#include "OutputFuzzySet.h"

namespace zadeh {

OutputFuzzySet operator||(const ::FuzzySet &lhs, const ::FuzzySet &rhs)
{
   OutputFuzzySet result;
   result.setMbs(std::max(lhs.getMbs(), rhs.getMbs()));
   return result;
}

OutputFuzzySet operator&&(const FuzzySet &lhs, const FuzzySet &rhs)
{
   OutputFuzzySet result;
   result.setMbs(std::min(lhs.getMbs(), rhs.getMbs()));
   return result;
}

OutputFuzzySet operator!(const FuzzySet &rhs)
{
   OutputFuzzySet result;
   result.setMbs(1 - rhs.getMbs());
   return result;
}

} // namespace zadeh

namespace lukasiewicz {

OutputFuzzySet operator||(const FuzzySet &lhs, const FuzzySet &rhs)
{
   OutputFuzzySet result;
   result.mbs_ = std::min(lhs.mbs_ + rhs.mbs_, 1.0);
   return result;
}

OutputFuzzySet operator&&(const FuzzySet &lhs, const FuzzySet &rhs)
{
   OutputFuzzySet result;
   result.mbs_ = std::max(lhs.mbs_ + rhs.mbs_ - 1.0, 0.0);
   return result;
}

OutputFuzzySet operator!(const FuzzySet &rhs)
{
   OutputFuzzySet result;
   result.mbs_ = 1 - rhs.mbs_;
   return result;
}

} // namespace lukasiewicz
