#include "SimBlock.h"
#include <iostream>

double dysysim::SimTime::delta_t = 1;
double dysysim::SimTime::t = 0;

std::map<int, dysysim::SimBlock *> dysysim::SimBlock::allSimBlocks_s;

bool dysysim::SimBlock::idIsUnique(int id)
{
   if (allSimBlocks_s.find(id) == end(allSimBlocks_s)) {
      return true;
   }
   std::cerr << "---- DYSYSIM simulation block id " << id
             << " already exists\n";
   return false;
}
