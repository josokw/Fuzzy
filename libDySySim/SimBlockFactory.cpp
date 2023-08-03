#include "SimBlockFactory.h"
#include "DySySim.h"
#include "DySySimControl.h"
#include "DySySimLogic.h"
#include "DySySimMath.h"
#include "ErrorCodes.h"
#include "Exceptions.h"
#include "SimBlock.h"

void dysysim::SimBlockFactory::add(const std::string &key,
                                   std::shared_ptr<SimBlock> tbm)
{
   if (not factory_.add(key, tbm)) {
      throw dysysim::FactoryAddError(key);
   }
}

void dysysim::SimBlockFactory::init()
{
   add("ADL", std::make_shared<dysysim::AlgebraicDelay>());
   add("ATT", std::make_shared<dysysim::Attenuator>());
   add("CON", std::make_shared<dysysim::Constant>());
   add("DIV", std::make_shared<dysysim::Divider>());
   add("DLY", std::make_shared<dysysim::Delay>());
   add("EUL", std::make_shared<dysysim::IntegratorEuler>());
   add("FIO", std::make_shared<dysysim::FirstOrder>());
   add("FRQ", std::make_shared<dysysim::Frequency>());
   add("GAIN", std::make_shared<dysysim::Gain>());
   add("INT", std::make_shared<dysysim::Integrator>());
   add("LIM", std::make_shared<dysysim::Limit>());
   add("LOG", std::make_shared<dysysim::Log>());
   add("MAX", std::make_shared<dysysim::Max>());
   add("MIN", std::make_shared<dysysim::Min>());
   add("MUL", std::make_shared<dysysim::Multiplier>());
   add("ONOFF", std::make_shared<dysysim::OnOff>());
   add("PI", std::make_shared<dysysim::PI>());
   add("PID", std::make_shared<dysysim::PID>());
   add("PLS", std::make_shared<dysysim::Puls>());
   add("STP", std::make_shared<dysysim::Step>());
   add("SUM", std::make_shared<dysysim::Summator>());
   add("TIME", std::make_shared<dysysim::Time>());
   add("ZOH", std::make_shared<dysysim::ZeroOrderHold>());
   add("RELAY", std::make_shared<dysysim::Relay>());
   add("SGN", std::make_shared<dysysim::Sign>());
   add("CLK", std::make_shared<dysysim::Clock>());
   // Logic
   add("AND", std::make_shared<dysysim::And>());
   add("OR", std::make_shared<dysysim::Or>());
   add("NOT", std::make_shared<dysysim::Not>());
   add("NAND", std::make_shared<dysysim::NAnd>());
   add("NOR", std::make_shared<dysysim::NOr>());
   add("XOR", std::make_shared<dysysim::XOr>());
   // Math
   add("ABS", std::make_shared<dysysim::Abs>());
   add("COS", std::make_shared<dysysim::Cos>());
   add("POL", std::make_shared<dysysim::Polynomial>());
   add("SIN", std::make_shared<dysysim::Sin>());
   add("SQRT", std::make_shared<dysysim::SquareRoot>());
   // Control
   add("HYS", std::make_shared<dysysim::Hysteresis>());
}

dysysim::SimBlockFactory::errors_t
dysysim::SimBlockFactory::configCheck(const std::string &key,
                                      const SimBlock::configData_t &cdata) const
{
   dysysim::SimBlockFactory::errors_t errs;

   if (factory_.isAvailable(key)) {
      auto pSBfactory = factory_.get(key);
      errs = pSBfactory->configDataIsOK(cdata);
      if (errs.empty()) {
         auto pSB = pSBfactory->create();
         auto err = pSB->config(cdata);
         SimBlock::allSimBlocks_s[pSB->getId()] = pSB;
      }
   } else {
      throw dysysim::FactoryUnknownTypeError(key);
   }

   return errs;
}
