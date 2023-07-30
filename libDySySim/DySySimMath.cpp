#include "DySySimMath.h"
#include "SimBlock.h"

dysysim::Cos::Cos()
   : SimBlock{"COS", SimBlock::ioType_t::inputoutput}
   , multipier_{1.0}
   , phase_{0.0}
{
   SimBlock::n_params_ = 2;
}

std::vector<std::error_code>
dysysim::Cos::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;

   return errs;
}

std::vector<std::error_code>
dysysim::Cos::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   return errs;
}

dysysim::Sin::Sin()
   : SimBlock{"SIN", SimBlock::ioType_t::inputoutput}
   , multiplier_{1.0}
   , phase_{0.0}
{
   SimBlock::n_params_ = 2;
}

std::vector<std::error_code>
dysysim::Sin::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;

   return errs;
}

std::vector<std::error_code>
dysysim::Sin::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   return errs;
}
