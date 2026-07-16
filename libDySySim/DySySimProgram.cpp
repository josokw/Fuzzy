#include "DySySimProgram.h"

dysysim::DySySimProgram::DySySimProgram()
   : factory_{context_}
{
   factory_.init();
}

void dysysim::DySySimProgram::setSimTime(double delta_t, double end_t)
{
   context_.sim_time.set(delta_t, end_t);
}

void dysysim::DySySimProgram::addBlock(const std::string &key,
                                       std::shared_ptr<SimBlock> block)
{
   factory_.add(key, std::move(block));
}

void dysysim::DySySimProgram::configureBlock(
   const std::string &type, const SimBlock::configData_t &cdata)
{
   auto errs = factory_.configCheck(type, cdata);
   errors_.insert(errors_.end(), errs.begin(), errs.end());
}

void dysysim::DySySimProgram::setStepCallback(step_callback_t cb)
{
   step_callback_ = std::move(cb);
}

dysysim::DySySimProgram::errors_t dysysim::DySySimProgram::run()
{
   if (errors_.empty()) {
      auto err = context_.setExeSequence();
      if (err) {
         errors_.push_back(err);
      }
   }

   if (errors_.empty()) {
      context_.initSimBlocks();
      do {
         context_.exeSimBlocks();
         if (step_callback_) {
            step_callback_(context_);
         }
      } while (context_.sim_time.simulation_is_on());
   }

   return errors_;
}
