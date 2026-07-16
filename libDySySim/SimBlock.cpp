#include "SimBlock.h"
#include "SimContext.h"

#include <algorithm>
#include <iostream>
#include <source_location>

static void
reportError(const std::string &blockType, const std::string &message,
            const std::source_location &loc = std::source_location::current())
{
   std::cerr << "---- " << blockType << " error: " << message << " ["
             << loc.file_name() << ":" << loc.line() << " in "
             << loc.function_name() << "]\n";
}

double dysysim::SimBlock::sumInputs() const
{
   double sum = 0.0;
   for (auto id : inputs_) {
      auto sign = (id < 0) ? -1 : 1;
      auto pSB = context_->getSimBlock(std::abs(id));
      if (pSB) {
         sum += sign * pSB->out_;
      }
   }
   return sum;
}

double dysysim::SimBlock::andInputs() const
{
   for (auto id : inputs_) {
      auto pSB = context_->getSimBlock(std::abs(id));
      if (pSB && dysysim::is_0(pSB->out_)) {
         return 0.0;
      }
   }
   return 1.0;
}

double dysysim::SimBlock::orInputs() const
{
   for (auto id : inputs_) {
      auto pSB = context_->getSimBlock(std::abs(id));
      if (pSB && dysysim::is_1(pSB->out_)) {
         return 1.0;
      }
   }
   return 0.0;
}

double dysysim::SimBlock::notInput() const
{
   auto pSB = context_->getSimBlock(std::abs(inputs_[0]));
   if (pSB && dysysim::is_1(pSB->out_)) {
      return 0.0;
   }
   return 1.0;
}

std::vector<std::error_code>
dysysim::SimBlock::configDataIsOK(const SimBlock::configData_t &config) const
{
   std::vector<std::error_code> errs;
   if (config.id <= 0) {
      errs.push_back(SimBlockErrc::ConfigIdError);
      reportError(blockType_,
                  "id = " + std::to_string(config.id) + " should be > 0");
   }
   if (context_ && !context_->idIsUnique(config.id)) {
      errs.push_back(SimBlockErrc::IdIsNotUniqueError);
      reportError(blockType_,
                  "id = " + std::to_string(config.id) + " is not unique");
   }

   switch (getIOType()) {
      case SimBlock::ioType::input0:
         if (config.inputs.size() != 0) {
            errs.push_back(SimBlockErrc::ConfigInputIdError);
            reportError(blockType_, "should not have inputs");
         }
         break;
      case SimBlock::ioType::input1:
         if (config.inputs.size() != 1) {
            errs.push_back(SimBlockErrc::ConfigInputIdError);
            reportError(blockType_, "should have 1 input");
         }
         break;
      case SimBlock::ioType::input2:
         if (config.inputs.size() != 2) {
            errs.push_back(SimBlockErrc::ConfigInputIdError);
            reportError(blockType_, "should have 2 inputs");
         }
         break;
      case SimBlock::ioType::input3:
         if (config.inputs.size() != 3) {
            errs.push_back(SimBlockErrc::ConfigInputIdError);
            reportError(blockType_, "should have 3 inputs");
         }
         break;
      case SimBlock::ioType::input1N:
      case SimBlock::ioType::input1Noutput0:
         if (config.inputs.size() == 0) {
            errs.push_back(SimBlockErrc::ConfigInputIdError);
            reportError(blockType_, "should have >= 1 inputs");
         }
         break;
      case SimBlock::ioType::input2N:
         if (config.inputs.size() < 2) {
            errs.push_back(SimBlockErrc::ConfigInputIdError);
            reportError(blockType_, "should have >= 2 inputs");
         }
         break;
   }

   if (config.parameters.size() != n_params(config)) {
      errs.push_back(SimBlockErrc::ConfigParameterError);
      reportError(blockType_, "should have " +
                                 std::to_string(n_params(config)) +
                                 " parameter(s)");
   }

   return errs;
}

std::error_code dysysim::SimBlock::allInputsAvailable()
{
   for (auto id : inputs_) {
      int absId = std::abs(id);
      if (!context_ || !context_->getSimBlock(absId)) {
         reportError(blockType_, "block id " + std::to_string(id_) +
                                    " references input id " +
                                    std::to_string(absId) +
                                    " which does not exist");
         return SimBlockErrc::ModelIsInconsistentError;
      }
   }
   return SimBlockErrc{};
}
