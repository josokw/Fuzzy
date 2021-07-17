#include "Connecting.h"
#include "SimBlock.h"
#include <iostream>

dysysim::SimBlock &operator>(dysysim::SimBlock &lhs, dysysim::SimBlock &rhs)
{
   std::cout << lhs.getId() << " --> " << rhs.getId() << std::endl;
   return rhs;
}

dysysim::SimBlock &operator+(dysysim::SimBlock &lhs, dysysim::SimBlock &rhs)
{
   dysysim::Summator *pSum = new dysysim::Summator;
   std::cout << "SUM " << lhs.getId() << " + " << rhs.getId() << std::endl;
   return *pSum;
}
