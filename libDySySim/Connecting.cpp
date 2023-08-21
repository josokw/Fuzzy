#include "Connecting.h"
#include "SimBlock.h"
#include <iostream>

dysysim::SimBlock &operator>>(double lhs, dysysim::SimBlock &rhs)
{
   std::cout << lhs << " --> " << rhs.getId() << std::endl;
   // rhs.inputs_[0] = lhs;
   return rhs;
}

dysysim::SimBlock &operator>>(dysysim::SimBlock &lhs, dysysim::SimBlock &rhs)
{
   std::cout << lhs.getId() << " --> " << rhs.getId() << std::endl;
   return rhs;
}

double operator+(dysysim::SimBlock &lhs, dysysim::SimBlock &rhs)
{
   return lhs.output() + rhs.output();
}
