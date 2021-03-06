#ifndef SIMBLOCKFACTORY_H
#define SIMBLOCKFACTORY_H

#include "GenericFactory.h"

namespace dysysim {

class SimBlock;

/// \todo Implement SimBlockFactory
class SimBlockFactory
{
public:
   SimBlockFactory() = default;
   bool add(const std::string &key, SimBlock *tbm)
   {
       return factory_.add(key, tbm);
   }
   auto size() const { return factory_.size(); }

private:
   GenericFactory<dysysim::SimBlock> factory_;
};

} // namespace dysysim

#endif