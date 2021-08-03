#ifndef SIMBLOCKFACTORY_H
#define SIMBLOCKFACTORY_H

#include "GenericFactory.h"
#include "SimBlock.h"

namespace dysysim {

class SimBlockFactory
{
public:
   SimBlockFactory() = default;
   ~SimBlockFactory() = default;

   void init();
   bool add(const std::string &key, SimBlock *tbm)
   {
      return factory_.add(key, tbm);
   }
   auto size() const { return factory_.size(); }
   SimBlock *create(const std::string &key) const
   {
      return factory_.create(key);
   }

private:
   GenericFactory<dysysim::SimBlock> factory_;
};

} // namespace dysysim

#endif