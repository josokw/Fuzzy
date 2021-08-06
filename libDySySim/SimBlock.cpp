#include "SimBlock.h"

#include <algorithm>
#include <iostream>

double dysysim::SimTime::delta_t = 1;
double dysysim::SimTime::end_t = 0.0;
double dysysim::SimTime::t = 0;

double dysysim::SimBlock::sumInputs() const
{
   double sum = 0.0;
   for (auto id : inputs_) {
      auto sign = (id < 0) ? -1 : 1;
      sum += sign * SimBlock::allSimBlocks_s[abs(id)]->out_;
   }
   return sum;
}

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
   return allSimBlocks_s.find(id) == end(allSimBlocks_s);
}

void dysysim::SimBlock::addSimBlock(int id, SimBlock *pSB)
{
   if (idIsUnique(id)) {
      allSimBlocks_s[id] = pSB;
   } else {
      std::cerr << "---- DySySim ERROR simulation block id " << id
                << " already exists\n";
   }
}

void dysysim::SimBlock::setExeSequence()
{
   exeSequence_s.clear();

   // First select all input0 SimBlocks
   for (auto [id, pSB] : allSimBlocks_s) {
      if (pSB->getIOType() == SimBlock::ioType::input0) {
         exeSequence_s.push_back(id);
      }
   }

   auto size_previous = exeSequence_s.size();
   auto size = exeSequence_s.size();
   do {
      size_previous = exeSequence_s.size();
      for (auto [id, pSB] : allSimBlocks_s) {
         if (std::find(begin(exeSequence_s), end(exeSequence_s), id) ==
             end(exeSequence_s)) {
            if (pSB->allInputsInExeSequence()) {
               exeSequence_s.push_back(id);
            }
         }
      }
      size = exeSequence_s.size();
   } while (size != size_previous);

   if (exeSequence_s.size() != dysysim::SimBlock::allSimBlocks_s.size()) {
      std::cerr << "---- DySySim ERROR simulation model contains id errors\n";
   }
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

bool dysysim::SimBlock::allInputsInExeSequence()
{
   bool result{true};
   for (auto id : inputs_) {
      if ((dysysim::SimBlock::allSimBlocks_s.find(abs(id)) ==
           end(dysysim::SimBlock::allSimBlocks_s)) and
          (dysysim::SimBlock::allSimBlocks_s[abs(id)]->getIOType() !=
           SimBlock::ioType::history)) {
         result = false;
         break;
      }
   }
   return result;
}
