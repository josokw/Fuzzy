#include "DySySimControl.h"

dysysim::Hysteresis::Hysteresis()
   : SimBlock{"HYS", SimBlock::ioType_t::input1N, 3}
   , out_t0_{0.0}
   , hysteresis_{0.0}
   , slope_{0.0}
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

   up_ = true;
   in_up_max_1_ = (1 - hysteresis_) / slope_;
   in_up_min_1_ = (-1 - hysteresis_) / slope_;
   in_down_max_1_ = (1 + hysteresis_) / slope_ ;
   in_down_min_1_ = (-1 + hysteresis_) / slope_;

   return errs;
}

std::vector<std::error_code>
dysysim::Hysteresis::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (errs.size() == 0) {
      if (std::abs(out_) > 1) {
         errs.push_back(SimBlockErrc::ConfigParameterRangeError);
      }
      if (hysteresis_ <= 0.0) {
         errs.push_back(SimBlockErrc::ConfigParameterRangeError);
      }
      if (slope_ <= 0.0) {
         errs.push_back(SimBlockErrc::ConfigParameterRangeError);
      }
   }

   return errs;
}

dysysim::PI::PI()
   : SimBlock{"PI", SimBlock::ioType_t::input1N, 3}
   , Kp_{1.0}
   , tau_I_{1.0}
   , z_{3, 0.0}
{
   has_history_ = true;
}

std::vector<std::error_code>
dysysim::PI::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   out_ = config.parameters[0];

   return errs;
}

std::vector<std::error_code>
dysysim::PI::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   return errs;
}

dysysim::PID::PID()
   : SimBlock{"PID", SimBlock::ioType_t::input1N, 3}
   , _Kp{1.0}
   , _tau_I{1.0}
   , _tau_D{1.0}
   , _z{4, 0.0}
{
   SimBlock::has_history_ = true;
}

std::vector<std::error_code>
dysysim::PID::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   out_ = config.parameters[0];

   return errs;
}

std::vector<std::error_code>
dysysim::PID::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   return errs;
}

dysysim::ZeroOrderHold::ZeroOrderHold()
   : SimBlock{"ZOH", SimBlock::ioType_t::input1N, 2}
   , nSamples_{1}
   , sample_{0}
{
   has_history_ = true;
}

std::vector<std::error_code>
dysysim::ZeroOrderHold::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;

   return errs;
}

std::vector<std::error_code> dysysim::ZeroOrderHold::configDataIsOK(
   const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   return errs;
}
