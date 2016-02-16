#include "Connecting.h"
#include "SimBlock.h"
#include <iostream>

void operator>>(dysysim::SimBlock& lhs, dysysim::SimBlock& rhs) {
   std::cout << lhs.getId() << " --> " << rhs.getId() << std::endl;
}
