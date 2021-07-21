#include "SimBlock.h"

#include <iostream>

double dysysim::SimTime::delta_t = 1;
double dysysim::SimTime::end_t = 0.0;
double dysysim::SimTime::t = 0;

void dysysim::SimTime::set(double delta, double end)
{
   dysysim::SimBlock::clearSimBlocks();
   reset();
   delta_t = delta;
   end_t = end;
}

bool dysysim::SimTime::simulation_on()
{
   if (t <= end_t) {
      dysysim::SimBlock::exeSimBlocks();
   }
   return t <= end_t;
}

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
