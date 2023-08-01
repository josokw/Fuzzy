#include "DySySimMath.h"
#include "SimBlock.h"

dysysim::Abs::Abs()
   : SimBlock{"ABS", SimBlock::ioType_t::input1N, 1}
   , multipier_{1.0}
{
}

std::vector<std::error_code>
dysysim::Abs::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   multipier_ = config.parameters[0];

   return errs;
}

std::vector<std::error_code>
dysysim::Abs::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   return errs;
}

dysysim::Cos::Cos()
   : SimBlock{"COS", SimBlock::ioType_t::input1, 2}
   , multipier_{1.0}
   , phase_{0.0}
{
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
   : SimBlock{"SIN", SimBlock::ioType_t::input1, 2}
   , multiplier_{1.0}
   , phase_{0.0}
{
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
