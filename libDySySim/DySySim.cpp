#include "DySySim.h"

std::vector<std::error_code>
dysysim::Constant::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   out_ = begin(config.parameters)[0];

   return errs;
}

std::vector<std::error_code>
dysysim::Constant::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should not have inputs\n";
   }
   if (config.parameters.size() != 1) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_ << " error: should have 1 parameter\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::AlgebraicDelay::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   out_ = out_previous_ = config.parameters[0];

   return errs;
}

std::vector<std::error_code> dysysim::AlgebraicDelay::configDataIsOK(
   const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() != 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have 1 input\n";
   }
   if (config.parameters.size() != 1) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_ << " error: should have 1 parameter\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Attenuator::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   attenuation_ = *begin(config.parameters);

   return errs;
}

std::vector<std::error_code>
dysysim::Attenuator::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   if (config.parameters.size() != 1) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_ << " error: should have 1 parameter\n";
   }
   return errs;
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
   if (config.parameters.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have no parameters\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Divider::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;

   return errs;
}

std::vector<std::error_code>
dysysim::Divider::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() != 2) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have 2 inputs\n";
   }
   if (config.parameters.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have no parameters\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Gain::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   auto par = begin(config.parameters);
   gain_ = par[0];

   return errs;
}

std::vector<std::error_code>
dysysim::Gain::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   if (config.parameters.size() != 1) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_ << " error: should have 1 parameter\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Limit::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   auto par = begin(config.parameters);
   min_ = par[0];
   max_ = par[1];

   return errs;
}

std::vector<std::error_code>
dysysim::Limit::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   if (config.parameters.size() != 2) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have 2 parameters\n";
   } else {
      if (config.parameters[0] >= config.parameters[1]) {
         errs.push_back(SimBlockErrc::ConfigParameterError);
         std::cerr << "---- " << blockType_
                   << " error: parameter_1 is not < parameter_2\n";
      }
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Max::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;

   return errs;
}

std::vector<std::error_code>
dysysim::Max::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   if (config.parameters.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have no parameters\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Min::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;

   return errs;
}

std::vector<std::error_code>
dysysim::Min::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   if (config.parameters.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have no parameters\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Multiplier::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;

   return errs;
}

std::vector<std::error_code>
dysysim::Multiplier::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   if (config.parameters.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have no parameters\n";
   }
   return errs;
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
   if (config.parameters.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have no parameters\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Summator::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;

   return errs;
}

std::vector<std::error_code>
dysysim::Summator::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   if (config.parameters.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have no parameters\n";
   }
   return errs;
}

// Sinus generator, amplitude = 1
std::vector<std::error_code>
dysysim::Frequency::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   auto par = begin(config.parameters);
   frequency_ = par[0];
   phase_ = par[1];

   return errs;
}

std::vector<std::error_code>
dysysim::Frequency::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have no inputs\n";
   }
   if (config.parameters.size() != 2) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have 2 parameters\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Step::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   auto par = begin(config.parameters);
   out_ = off_ = par[0];
   on_ = par[1];
   t_on_ = par[2];

   return errs;
}

std::vector<std::error_code>
dysysim::Step::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have no inputs\n";
   }
   if (config.parameters.size() != 3) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have 3 parameters\n";
   } else {
      if (config.parameters[2] <= 0) {
         errs.push_back(SimBlockErrc::ConfigParameterError);
         std::cerr << "---- " << blockType_
                   << " error: parameter 3 should be > 0\n";
      }
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Puls::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   auto par = begin(config.parameters);
   out_ = off_ = par[0];
   on_ = par[1];
   t_on_ = par[2];
   t_off_ = par[3];

   return errs;
}

std::vector<std::error_code>
dysysim::Puls::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have no inputs\n";
   }
   if (config.parameters.size() != 4) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have 4 parameters\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Time::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   out_ = 0.0;

   return errs;
}

std::vector<std::error_code>
dysysim::Time::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have no inputs\n";
   }
   if (config.parameters.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have no parameters\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Delay::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   auto par = begin(config.parameters);
   out_ = out_t0_ = par[0];
   delaytime_ = par[1];
   for (int i = 0; i < int(delaytime_ / SimTime::delta_t); i++) {
      buffer_.push(out_t0_);
   }

   return errs;
}

std::vector<std::error_code>
dysysim::Delay::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   if (config.parameters.size() != 2) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have 2 parameters\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::FirstOrder::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   auto par = begin(config.parameters);
   timeConstant_ = par[0];
   out_ = par[1];

   return errs;
}

std::vector<std::error_code>
dysysim::FirstOrder::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   if (config.parameters.size() != 2) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have 2 parameters\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::OnOff::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   auto par = begin(config.parameters);
   out_ = off_ = par[0];
   on_ = par[1];
   onoff_ = par[2];

   return errs;
}

std::vector<std::error_code>
dysysim::OnOff::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() != 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have 1 input\n";
   }
   if (config.parameters.size() != 3) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have 3 parameters\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Integrator::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   auto par = begin(config.parameters);
   out_ = par[0];

   return errs;
}

std::vector<std::error_code>
dysysim::Integrator::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   if (config.parameters.size() != 1) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_ << " error: should have 1 parameter\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::IntegratorEuler::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   auto par = begin(config.parameters);
   out_ = par[0];

   return errs;
}

std::vector<std::error_code> dysysim::IntegratorEuler::configDataIsOK(
   const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   if (config.parameters.size() != 1) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_ << " error: should have 1 parameter\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::PI::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   auto par = begin(config.parameters);
   out_ = par[0];

   return errs;
}

std::vector<std::error_code>
dysysim::PI::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   if (config.parameters.size() != 3) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have 3 parameters\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::PID::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   auto par = begin(config.parameters);
   out_ = par[0];

   return errs;
}

std::vector<std::error_code>
dysysim::PID::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   if (config.parameters.size() != 3) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have 3 parameters\n";
   }
   return errs;
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
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   if (config.parameters.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_
                << " error: should have no parameters\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Log::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   parameters_ = std::vector<int>(config.parameters.size());
   for (auto index = 0; auto &e : parameters_) {
      e = int(config.parameters[index++]);
   }

   return errs;
}

std::vector<std::error_code>
dysysim::Log::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have >= 1 input\n";
   }
   if (config.parameters.size() != (2 * config.inputs.size())) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_ << " error: should have "
                << (2 * config.inputs.size()) << " parameters\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Relay::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   auto par = begin(config.parameters);
   ref_ = par[0];

   return errs;
}

std::vector<std::error_code>
dysysim::Relay::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() != 3) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have 3 inputs\n";
   }
   if (config.parameters.size() != 1) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_ << " error: should have 1 parameter\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::And::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;

   return errs;
}

std::vector<std::error_code>
dysysim::And::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 2) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have > 1 inputs\n";
   }
   if (config.parameters.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_ << " error: should have 0 parameter\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Or::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;

   return errs;
}

std::vector<std::error_code>
dysysim::Or::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 2) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have > 1 inputs\n";
   }
   if (config.parameters.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_ << " error: should have 0 parameter\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Not::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;

   return errs;
}

std::vector<std::error_code>
dysysim::Not::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() != 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have 1 input\n";
   }
   if (config.parameters.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_ << " error: should have 0 parameter\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::NAnd::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;

   return errs;
}

std::vector<std::error_code>
dysysim::NAnd::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 2) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have > 1 inputs\n";
   }
   if (config.parameters.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_ << " error: should have 0 parameter\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::NOr::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;

   return errs;
}

std::vector<std::error_code>
dysysim::NOr::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 2) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have > 1 inputs\n";
   }
   if (config.parameters.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_ << " error: should have 0 parameter\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::XOr::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;

   return errs;
}

std::vector<std::error_code>
dysysim::XOr::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() < 2) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have > 1 inputs\n";
   }
   if (config.parameters.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_ << " error: should have 0 parameter\n";
   }
   return errs;
}

std::vector<std::error_code>
dysysim::Sign::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;

   return errs;
}

std::vector<std::error_code>
dysysim::Sign::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() != 1) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have 1 input\n";
   }
   if (config.parameters.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_ << " error: should have 0 parameter\n";
   }
   return errs;
}

// Sinus generator, amplitude = 1
std::vector<std::error_code>
dysysim::Clock::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   auto par = begin(config.parameters);
   frequency_ = par[0];

   return errs;
}

std::vector<std::error_code>
dysysim::Clock::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);
   if (config.inputs.size() != 0) {
      errs.push_back(SimBlockErrc::ConfigInputIdError);
      std::cerr << "---- " << blockType_ << " error: should have no inputs\n";
   }
   if (config.parameters.size() != 1) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      std::cerr << "---- " << blockType_ << " error: should have 1 parameter\n";
   }
   return errs;
}