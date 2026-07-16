#ifndef DYSYSIMPROGRAM_H
#define DYSYSIMPROGRAM_H

#include "SimBlock.h"
#include "SimBlockFactory.h"
#include "SimContext.h"

#include <functional>
#include <memory>
#include <system_error>
#include <vector>

namespace dysysim {

/// DySySimProgram owns a SimContext and SimBlockFactory, provides methods to
/// configure blocks, set simulation time, and run the simulation.
class DySySimProgram
{
public:
   using errors_t = std::vector<std::error_code>;
   using step_callback_t = std::function<void(SimContext &)>;

   DySySimProgram();
   ~DySySimProgram() = default;

   DySySimProgram(const DySySimProgram &) = delete;
   DySySimProgram &operator=(const DySySimProgram &) = delete;

   void setSimTime(double delta_t, double end_t);
   void addBlock(const std::string &key, std::shared_ptr<SimBlock> block);
   void configureBlock(const std::string &type,
                       const SimBlock::configData_t &cdata);
   void setStepCallback(step_callback_t cb);
   [[nodiscard]] errors_t run();

   SimContext &context() { return context_; }
   const SimContext &context() const { return context_; }

private:
   SimContext context_;
   SimBlockFactory factory_;
   errors_t errors_;
   step_callback_t step_callback_;
};

} // namespace dysysim

#endif // DYSYSIMPROGRAM_H
