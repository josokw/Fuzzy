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
   out_ = config.parameters[0];
   hysteresis_ = config.parameters[1];
   slope_ = config.parameters[2];

   return errs;
}

std::vector<std::error_code>
dysysim::Hysteresis::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
  
   return errs;
}
