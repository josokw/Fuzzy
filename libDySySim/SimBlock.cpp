#include "SimBlock.h"
#include "ErrorCodes.h"

#include <algorithm>
#include <iostream>

double dysysim::SimTime::delta_t = 1;
double dysysim::SimTime::end_t = 0.0;
int dysysim::SimTime::width_t = 8;
int dysysim::SimTime::precision_t = 3;
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

double dysysim::SimBlock::andInputs() const
{
   for (auto id : inputs_) {
      // Lazy evaluation of inputs
      if (dysysim::is_0(SimBlock::allSimBlocks_s[id]->out_)) {
         return 0.0;
      }
   }
   return 1.0;
}

double dysysim::SimBlock::orInputs() const
{
   for (auto id : inputs_) {
      // Lazy evaluation of inputs
      if (dysysim::is_1(SimBlock::allSimBlocks_s[id]->out_)) {
         return 1.0;
      }
   }
   return 0.0;
}

double dysysim::SimBlock::notInput() const
{
   if (dysysim::is_1(SimBlock::allSimBlocks_s[inputs_[0]]->out_)) {
      return 0.0;
   }
   return 1.0;
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
   if (t < end_t) {
      dysysim::SimBlock::exeSimBlocks();
   }
   return t < end_t;
}

std::map<int, std::shared_ptr<dysysim::SimBlock>>
   dysysim::SimBlock::allSimBlocks_s;
std::vector<int> dysysim::SimBlock::exeSequence_s;

bool dysysim::SimBlock::idIsUnique(int id)
{
   return allSimBlocks_s.find(id) == end(allSimBlocks_s);
}

std::error_code dysysim::SimBlock::addSimBlock(int id,
                                               std::shared_ptr<SimBlock> pSB)
{
   if (idIsUnique(id)) {
      allSimBlocks_s[id] = std::move(pSB);
      return SimBlockErrc::IdIsNotUniqueError;
   }
   return SimBlockErrc{};
}

std::error_code dysysim::SimBlock::setExeSequence()
{
   exeSequence_s.clear();
   auto const size = allSimBlocks_s.size();

   // First select all input0 SimBlocks
   for (const auto &[id, pSB] : allSimBlocks_s) {
      if (pSB->getIOType() == SimBlock::ioType::input0) {
         exeSequence_s.push_back(id);
      }
   }

   auto size_exeSeq = exeSequence_s.size();
   int max_count = 50;
   int c = 0;
   while (size_exeSeq < size && c < max_count) {
      ++c;
      for (const auto &[id, pSB] : allSimBlocks_s) {
         if (not pSB->IdInExeSequence(id)) {
            auto error = pSB->allInputsAvailable();
            if (error != SimBlockErrc{}) {
               return error;
            }
            else {
               exeSequence_s.push_back(id);
               size_exeSeq = exeSequence_s.size();
            }
         }
      }
   }

   if (exeSequence_s.size() != dysysim::SimBlock::allSimBlocks_s.size()) {
      return SimBlockErrc::ModelIsInconsistentError;
   }

   return SimBlockErrc{};
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

std::vector<std::error_code>
dysysim::SimBlock::configDataIsOK(const SimBlock::configData_t &config) const
{
   std::vector<std::error_code> errs;
   if (config.id <= 0) {
      errs.push_back(SimBlockErrc::ConfigIdError);
      std::cerr << "---- DySySim error: id = " << config.id << " <= 0\n";
   }
   if (not SimBlock::idIsUnique(config.id)) {
      errs.push_back(SimBlockErrc::IdIsNotUniqueError);
      std::cerr << "---- DySySim error: id = " << config.id
                << " is not unique\n";
   }
   return errs;
}

std::error_code dysysim::SimBlock::allInputsAvailable()
{
   for (auto id : inputs_) {
      if ((dysysim::SimBlock::allSimBlocks_s.find(abs(id)) ==
           end(dysysim::SimBlock::allSimBlocks_s))) {
         return SimBlockErrc::ModelIsInconsistentError;
      }
   }
   return SimBlockErrc{};
}

bool dysysim::SimBlock::allInputsInExeSequence()
{
   for (auto id : inputs_) {
      if (std::find(begin(dysysim::SimBlock::exeSequence_s),
                    end(dysysim::SimBlock::exeSequence_s),
                    abs(id)) == end(dysysim::SimBlock::exeSequence_s) and
          (dysysim::SimBlock::allSimBlocks_s[abs(id)]->getIOType() !=
           SimBlock::ioType::history)) {
         return false;
      }
   }
   return true;
}

bool dysysim::SimBlock::IdInExeSequence(int id)
{
   return (std::find(begin(exeSequence_s), end(exeSequence_s), id) !=
           end(exeSequence_s));
}
