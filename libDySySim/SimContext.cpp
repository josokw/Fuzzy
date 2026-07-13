#include "SimContext.h"
#include "SimBlock.h"

#include <algorithm>
#include <iostream>

void dysysim::SimTime::set(double delta, double end)
{
   reset();
   delta_t = delta;
   end_t = end;
}

bool dysysim::SimTime::simulation_is_on() const
{
   return t < end_t;
}

void dysysim::SimContext::clear()
{
   allSimBlocks_.clear();
   exeSequence_.clear();
}

bool dysysim::SimContext::idIsUnique(int id) const
{
   return allSimBlocks_.find(id) == allSimBlocks_.end();
}

std::error_code dysysim::SimContext::addSimBlock(int id,
                                                  std::shared_ptr<SimBlock> pSB)
{
   if (idIsUnique(id)) {
      pSB->setContext(this);
      allSimBlocks_[id] = std::move(pSB);
      return SimBlockErrc{};
   }
   return SimBlockErrc::IdIsNotUniqueError;
}

std::shared_ptr<dysysim::SimBlock> dysysim::SimContext::getSimBlock(int id)
{
   auto it = allSimBlocks_.find(id);
   if (it != allSimBlocks_.end()) {
      return it->second;
   }
   return nullptr;
}

std::error_code dysysim::SimContext::setExeSequence()
{
   exeSequence_.clear();
   auto const size = allSimBlocks_.size();

   // First select all input0 SimBlocks
   for (const auto &[id, pSB] : allSimBlocks_) {
      if (pSB->getIOType() == SimBlock::ioType_t::input0) {
         exeSequence_.push_back(id);
      }
   }

   auto size_exeSeq = exeSequence_.size();
   int max_count = 50;
   int c = 0;
   while (size_exeSeq < size && c < max_count) {
      ++c;
      for (const auto &[id, pSB] : allSimBlocks_) {
         if (std::find(exeSequence_.begin(), exeSequence_.end(), id) ==
             exeSequence_.end()) {
            bool allFound = true;
            for (auto inputId : pSB->getInputs()) {
               int absId = std::abs(inputId);
               if (std::find(exeSequence_.begin(), exeSequence_.end(), absId) ==
                       exeSequence_.end() &&
                   !allSimBlocks_[absId]->hasHistory()) {
                  allFound = false;
                  break;
               }
            }
            if (allFound) {
               exeSequence_.push_back(id);
               size_exeSeq = exeSequence_.size();
            }
         }
      }
   }

   std::cout << "..   exe sequence: ";
   for (auto &id : exeSequence_) {
      std::cout << id << " ";
   }
   std::cout << std::endl;

   if (exeSequence_.size() != allSimBlocks_.size()) {
      return SimBlockErrc::ModelIsInconsistentError;
   }

   return SimBlockErrc{};
}

void dysysim::SimContext::setExeSequence(std::vector<int> &exeSequence)
{
   exeSequence_ = exeSequence;
}

void dysysim::SimContext::initSimBlocks()
{
   for (auto id : exeSequence_) {
      auto pSB = getSimBlock(id);
      if (pSB) {
         pSB->exe();
      }
   }
}

void dysysim::SimContext::exeSimBlocks()
{
   sim_time.next();
   for (auto id : exeSequence_) {
      auto pSB = getSimBlock(id);
      if (pSB) {
         pSB->exe();
      }
   }
}
