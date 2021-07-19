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

   void config(const SimBlock::configData_t &config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
   }
   virtual void next() const = 0;

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
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }

   virtual void next() const
   {
      //      std::cout << _blockType << " ";
      //      for (auto i: _ids) {
      //         std::cout << i << " ";
      //         auto sb {getSimBlock(i)};
      //         std::cout << i << ": " << sb->getBlockType() << "  ";
      //      }
      //      std::cout << std::endl;
   }

private:
   // std::ostream _ofs;
};

} // namespace dysysim

#endif // SIMBLOCKI_H
