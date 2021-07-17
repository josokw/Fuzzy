#include "DySySim.h"

void dysysim::Constant::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
   out_ = begin(config.parameters)[0];
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
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
   attenuation_ = *begin(config.parameters);
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
}

void dysysim::Limit::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
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
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
}

// Timed output blocks
// ---------------------------------------------------------

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
   id_ = config.id;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
   auto par = begin(config.parameters);
   step_out_ = par[0];
   step_t_ = par[1];
}

void dysysim::Time::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
   SimTime::delta_t = *begin(config.parameters);
}

void dysysim::Delay::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
   auto par = begin(config.parameters);
   auto initial_out_ = par[0];
   for (int i = 0; i < int(delaytime_ / SimTime::delta_t); i++) {
      buffer_.push(initial_out_);
   }
}

void dysysim::FirstOrder::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
   timeConstant_ = *begin(config.parameters);
}

void dysysim::OnOff::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::idIsUnique(id_)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
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
