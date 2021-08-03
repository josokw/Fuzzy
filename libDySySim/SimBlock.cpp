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
std::vector<int> dysysim::SimBlock::exeSequence_s;

bool dysysim::SimBlock::idIsUnique(int id)
{
   if (allSimBlocks_s.find(id) == end(allSimBlocks_s)) {
      return true;
   }
   std::cerr << "---- DYSYSIM simulation block id " << id
             << " already exists\n";
   return false;
}

void dysysim::SimBlock::setExeSequence()
{
   std::cerr << "---- DYSYSIM " << __func__ << "() not yet implemented\n";
}

void dysysim::SimBlock::setExeSequence(std::vector<int> &exeSequence)
{
   exeSequence_s = exeSequence;
}

void dysysim::SimBlock::initSimBlocks()
{
   for (auto id : exeSequence_s) {
      auto pSB = getSimBlock(id);
      if (pSB and ((pSB->getIOType() == SimBlock::ioType::output0) or
                   (pSB->getIOType() == SimBlock::ioType::inputoutput))) {
         pSB->exe();
      }
   }
}

void dysysim::SimBlock::exeSimBlocks()
{
   dysysim::SimTime::next();
   for (auto id : exeSequence_s) {
      auto pSB = getSimBlock(id);
      if (pSB) {
         pSB->exe();
      }
   }
}
