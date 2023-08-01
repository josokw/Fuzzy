#include "DySySimControl.h"

dysysim::Hysteresis::Hysteresis()
   : SimBlock{"HYS", SimBlock::ioType_t::input1N, 3}
   , out_t0_{0.0}
   , hysteresis_{1.0}
   , slope_{1.0}
{
   has_history_ = true;
}

std::vector<std::error_code>
dysysim::Hysteresis::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   auto par = begin(config.parameters);
   out_ = par[0];
   hysteresis_ = par[1];
   slope_ = par[2];

   return errs;
}

std::vector<std::error_code>
dysysim::Hysteresis::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   return errs;
}
