#ifndef SIMBLOCKI_H
#define SIMBLOCKI_H

#include "SimBlock.h"

#include <cassert>
#include <initializer_list>
#include <vector>

namespace dysysim {

class SimBlockI : public SimBlock
{
public:
   SimBlockI()
      : SimBlock{}
      , inputs_{}
   {
   }

protected:
   std::vector<int> inputs_;
};

class TimedSimBlockI : public TimedSimBlock
{
public:
   TimedSimBlockI()
      : TimedSimBlock()
   {
   }
   virtual ~TimedSimBlockI() = default;

   // void config(const SimBlock::configData_t &config) override
   // {
   //    id_ = config.id;
   //    inputs_ = config.inputs;
   //    if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
   //       SimBlock::allSimBlocks_s[id_] = this;
   //    }
   // }

protected:
   std::vector<int> inputs_;
};

class Log : public SimBlockI
{
public:
   Log()
      : SimBlockI{}
   {
      blockType_ = "LOG";
   }

   void config(const SimBlock::configData_t &config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) == end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }

   void exe() override
   {
      for (auto id: inputs_)
      {
         auto pSB = SimBlock::getSimBlock(id);
         std::cerr << id << " " << pSB->getBlockType() << "\n";
      }
   }
};

} // namespace dysysim

#endif // SIMBLOCKI_H
