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
   in_up_max_1_ = (1 + hysteresis_ * slope_) / slope_;
   in_up_min_1_ = (-1 + hysteresis_ * slope_) / slope_;
   in_down_max_1_ = (1 - hysteresis_ * slope_) / slope_;
   in_down_min_1_ = (-1 - hysteresis_ * slope_) / slope_;

   return errs;
}

std::vector<std::error_code>
dysysim::Hysteresis::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (errs.size() == 0) {
      if (std::abs(config.parameters[0]) > 1) {
         errs.push_back(SimBlockErrc::ConfigParameterRangeError);
         std::cerr << "---- " << blockType_
                   << " error: parameter 1 =" << config.parameters[2]
                   << " should be <= 1 and >= -1\n";
      }
      if (config.parameters[1] <= 0.0) {
         errs.push_back(SimBlockErrc::ConfigParameterRangeError);
         std::cerr << "---- " << blockType_
                   << " error: parameter 2 = " << config.parameters[2]
                   << " should be > 0\n";
      }
      if (config.parameters[2] <= 0.0) {
         errs.push_back(SimBlockErrc::ConfigParameterRangeError);
         std::cerr << "---- " << blockType_
                   << " error: parameter 3 = " << config.parameters[2]
                   << " should be > 0\n";
      }
   }

   return errs;
}

dysysim::PI::PI()
   : SimBlock{"PI", SimBlock::ioType_t::input1N, 3}
   , Kp_{0.0}
   , tau_I_{0.0}
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
   Kp_ = config.parameters[1];
   tau_I_ = config.parameters[2];

   return errs;
}

std::vector<std::error_code>
dysysim::PI::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (errs.size() == 0) {
      if (config.parameters[1] < 0) {
         errs.push_back(SimBlockErrc::ConfigParameterRangeError);
         std::cerr << "---- " << blockType_ << " error: parameter 2 "
                   << config.parameters[2] << " should be >= 0\n";
      }
      if (config.parameters[2] < 0) {
         errs.push_back(SimBlockErrc::ConfigParameterRangeError);
         std::cerr << "---- " << blockType_ << " error: parameter 3 "
                   << config.parameters[2] << " should be >= 0\n";
      }
   }
   return errs;
}

dysysim::PID::PID()
   : SimBlock{"PID", SimBlock::ioType_t::input1N, 3}
   , _Kp{1.0}
   , _tau_I{0.0}
   , _tau_D{0.0}
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
   if (errs.size() == 0) {
      if (config.parameters[1] < 0) {
         errs.push_back(SimBlockErrc::ConfigParameterRangeError);
         std::cerr << "---- " << blockType_ << " error: parameter 2 "
                   << config.parameters[2] << " should be >= 0\n";
      }
      if (config.parameters[2] < 0) {
         errs.push_back(SimBlockErrc::ConfigParameterRangeError);
         std::cerr << "---- " << blockType_ << " error: parameter 3"
                   << config.parameters[2] << " should be >= 0\n";
      }
      if (config.parameters[3] < 0) {
         errs.push_back(SimBlockErrc::ConfigParameterRangeError);
         std::cerr << "---- " << blockType_ << " error: parameter 4"
                   << config.parameters[2] << " should be >= 0\n";
      }
   }
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
