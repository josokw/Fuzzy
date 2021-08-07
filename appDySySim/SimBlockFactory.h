#ifndef SIMBLOCKFACTORY_H
#define SIMBLOCKFACTORY_H

#include "GenericFactory.h"
#include "SimBlock.h"

namespace dysysim {

/// Creates dynamically SimBlock objects based on a unique std::string key
/// value.
class SimBlockFactory
{
public:
   SimBlockFactory() = default;
   ~SimBlockFactory() = default;

   void add(const std::string &key, SimBlock *tbm);
   void init();
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
