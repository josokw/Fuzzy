#include "SimBlockHC.h"

#include <numeric>

dysysim::SimBlockHC &operator>>(double lhs, dysysim::SimBlockHC &rhs)
{
   rhs[0] = lhs;
   return rhs;
}

dysysim::SimBlockHC &operator>>(dysysim::SimBlockHC &lhs,
                                dysysim::SimBlockHC &rhs)
{
   rhs[0] = lhs.output();
   return rhs;
}

double dysysim::SimBlockHC::sumInputs() const
{
   return std::accumulate(inputs_.begin(), inputs_.end(), 0.0);
}