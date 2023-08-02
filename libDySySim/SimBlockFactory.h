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
   using errors_t = std::vector<std::error_code>;
   
   SimBlockFactory() = default;
   ~SimBlockFactory() = default;

   void add(const std::string &key, std::shared_ptr<SimBlock> tbm);
   void init();
   auto size() const { return factory_.size(); }

   /// Uses a SimBlock in the factory for checking the config data.
   errors_t
   configCheck(const std::string &key,
               const SimBlock::configData_t &cdata) const;

   std::shared_ptr<dysysim::SimBlock> create(const std::string &key) const
   {
      return factory_.create(key);
   }

private:
   GenericFactory<dysysim::SimBlock> factory_;
};

} // namespace dysysim

#endif
