#include "DySySim.h"

void dysysim::Constant::config(const SimBlock::configData_t &config)
{
   if (configDataIsOK(config)) {
      id_ = config.id;
      if (SimBlock::idIsUnique(id_)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
      out_ = begin(config.parameters)[0];
   }
}

bool dysysim::Constant::configDataIsOK(
   const SimBlock::configData_t &config) const
{
   bool ok = (config.id > 0) and (config.inputs.size() == 0) and
             (config.parameters.size() == 1);
   if (not ok) {
      std::cerr << "---- DySySim error " << config.id << blockType_
                << " config() not correct\n";
   }
   return ok;
}

void dysysim::AlgebraicDelay::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
}

void dysysim::Attenuator::config(const SimBlock::configData_t &config)
{
   if (configDataIsOK(config)) {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::idIsUnique(id_)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
      attenuation_ = *begin(config.parameters);
   }
}

bool dysysim::Attenuator::configDataIsOK(
   const SimBlock::configData_t &config) const
{
   bool ok = (config.id > 0) and (config.inputs.size() == 0) and
             (config.parameters.size() == 1);
   if (not ok) {
      std::cerr << "---- DySySim error '" << config.id << " " << blockType_
                << "' config() not correct\n";
   }
   return ok;
}

void dysysim::Cos::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
}

void dysysim::Divider::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
}

void dysysim::Gain::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
   auto par = begin(config.parameters);
   gain_ = par[0];
}

void dysysim::Limit::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
   auto par = begin(config.parameters);
   min_ = par[0];
   max_ = par[1];
}

void dysysim::Max::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
}

void dysysim::Min::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
}

void dysysim::Multiplier::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
}

void dysysim::Sin::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
}

void dysysim::Summator::config(const SimBlock::configData_t &config)
{
   if (configDataIsOK(config)) {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::idIsUnique(id_)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }
}

bool dysysim::Summator::configDataIsOK(
   const SimBlock::configData_t &config) const
{
   bool ok = (config.id > 0) and (config.inputs.size() > 1) and
             (config.parameters.size() == 0);
   if (not ok) {
      std::cerr << "---- DySySim error '" << config.id << " " << blockType_
                << "' config() not correct\n";
   }
   return ok;
}

// Sinus generator, amplitude = 1
void dysysim::Frequency::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
}

void dysysim::Step::config(const SimBlock::configData_t &config)
{
   if (configDataIsOK(config)) {
      id_ = config.id;
      if (SimBlock::idIsUnique(id_)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
      auto par = begin(config.parameters);
      out_ = off_ = par[0];
      on_ = par[1];
      t_on_ = par[2];
   }
}

bool dysysim::Step::configDataIsOK(const SimBlock::configData_t &config) const
{
   bool ok = (config.id > 0) and (config.inputs.size() == 0) and
             (config.parameters.size() == 3) and (config.parameters[2] > 0);
   if (not ok) {
      std::cerr << "---- DySySim error " << config.id << blockType_
                << " config() not correct\n";
   }
   return ok;
}

void dysysim::Puls::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
   auto par = begin(config.parameters);
   out_ = off_ = par[0];
   on_ = par[1];
   t_on_ = par[2];
   t_off_ = par[3];
}

void dysysim::Time::config(const SimBlock::configData_t &config)
{
   if (configDataIsOK(config)) {
      id_ = config.id;
      if (SimBlock::idIsUnique(id_)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
      out_ = 0.0;
   }
}

bool dysysim::Time::configDataIsOK(const SimBlock::configData_t &config) const
{
   bool ok = (config.id > 0) and (config.inputs.size() == 0) and
             (config.parameters.size() == 0);
   if (not ok) {
      std::cerr << "---- DySySim error " << config.id << " " << blockType_
                << " config() not correct\n";
   }
   return ok;
}

void dysysim::Delay::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
   auto par = begin(config.parameters);
   out_t0_ = par[0];
   delaytime_ = par[1];
   for (int i = 0; i < int(delaytime_ / SimTime::delta_t); i++) {
      buffer_.push(out_t0_);
   }
   std::cout << "Delay buffer = " << buffer_.size() << "\n";
}

void dysysim::FirstOrder::config(const SimBlock::configData_t &config)
{
   if (configDataIsOK(config)) {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::idIsUnique(id_)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
      auto par = begin(config.parameters);
      timeConstant_ = par[0];
      out_ = par[1];
   }
}

bool dysysim::FirstOrder::configDataIsOK(
   const SimBlock::configData_t &config) const
{
   bool ok = (config.id > 0) and (config.inputs.size() > 0) and
             (config.parameters.size() == 2);
   if (not ok) {
      std::cerr << "---- DySySim error '" << config.id << " " << blockType_
                << "' config() not correct\n";
   }
   return ok;
}

void dysysim::OnOff::config(const SimBlock::configData_t &config)
{
   if (configDataIsOK(config)) {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::idIsUnique(id_)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
      auto par = begin(config.parameters);
      out_ = off_ = par[0];
      on_ = par[1];
      onoff_ = par[2];
   }
}

bool dysysim::OnOff::configDataIsOK(const SimBlock::configData_t &config) const
{
   bool ok = (config.id > 0) and (config.inputs.size() == 1) and
             (config.parameters.size() == 3);
   if (not ok) {
      std::cerr << "---- DySySim error '" << config.id << " " << blockType_
                << "' config() not correct\n";
   }
   return ok;
}

void dysysim::Integrator::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
}

void dysysim::IntegratorEuler::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
}

void dysysim::IntegratorTrapezoidal::config(
   const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
}

void dysysim::PI::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
}

void dysysim::PID::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
}

void dysysim::ZeroOrderHold::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
}
