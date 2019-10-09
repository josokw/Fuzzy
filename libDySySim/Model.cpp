#include "Model.h"
#include <iostream>

std::ostream &dysysim::Model::write(std::ostream &os) const
{
   os << _name << std::endl;
   //   for (const auto& sb: _time.getSimBlocks()) {
   //      std::cout << sb.first << " ";
   //   }
   std::cout << std::endl;
   return os;
}

void dysysim::Model::simulate(int steps)
{
   connect();
   for (int tn = 0; tn < steps; ++tn) {
      //_logger.output();
      _time.next();
   }
}

void dysysim::Model::connect() {}
