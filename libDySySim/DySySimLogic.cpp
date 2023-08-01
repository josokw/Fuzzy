#include "DySySimLogic.h"

dysysim::And::And()
   : SimBlock{"AND", SimBlock::ioType_t::input2N}
{
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
   return errs;
}

dysysim::Or::Or()
   : SimBlock{"OR", SimBlock::ioType_t::input2N}
{
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
   return errs;
}

dysysim::Not::Not()
   : SimBlock{"NOT", SimBlock::ioType_t::input1}
{
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
   return errs;
}

dysysim::NAnd::NAnd()
   : SimBlock{"NAND", SimBlock::ioType_t::input2N}
{
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
   return errs;
}

dysysim::NOr::NOr()
   : SimBlock{"NOR", SimBlock::ioType_t::input2N}
{
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
   return errs;
}

dysysim::XOr::XOr()
   : SimBlock{"XOR", SimBlock::ioType_t::input2N}
{
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
   return errs;
}
