#include "DySySimMath.h"
#include "SimBlock.h"

dysysim::Abs::Abs()
   : SimBlock{"ABS", SimBlock::ioType_t::input1N, 1}
   , multipier_{1.0}
{
}

std::vector<std::error_code>
dysysim::Abs::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   multipier_ = config.parameters[0];

   return errs;
}

std::vector<std::error_code>
dysysim::Abs::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);

   return errs;
}

dysysim::Cos::Cos()
   : SimBlock{"COS", SimBlock::ioType_t::input1, 2}
   , multipier_{1.0}
   , phase_{0.0}
{
}

std::vector<std::error_code>
dysysim::Cos::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   multipier_ = config.parameters[0];
   phase_ = config.parameters[1];

   return errs;
}

std::vector<std::error_code>
dysysim::Cos::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);

   return errs;
}

dysysim::Polynomial::Polynomial()
   : SimBlock{"POL", SimBlock::ioType_t::input1N, 1}
   , degree_{0}
   , coefficients_{}
{
}

std::vector<std::error_code>
dysysim::Polynomial::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   // degree_ = 0;
   std::cout << "#param = " << config.parameters.size() << std::endl;
   if (config.parameters.size() > 1) {
      coefficients_ = std::vector<double>(config.parameters.size() - 1);
      for (auto indx = 0; auto const p : config.parameters) {
         if (indx == 0) {
            degree_ = p;
            std::cout << "degree = " << degree_ << std::endl;
         } else {
            coefficients_[indx - 1] = p;
         }
         ++indx;
      }
   }

   return errs;
}

std::vector<std::error_code>
dysysim::Polynomial::configDataIsOK(const SimBlock::configData_t &config) const
{
   std::vector<std::error_code> errs;

   if (config.parameters.size() < 3) {
      errs.push_back(SimBlockErrc::ConfigNumberOfParametersError);
      return errs;
   }
   if (int(config.parameters[0]) < 1 )
   {
      errs.push_back(SimBlockErrc::ConfigParameterRangeError);
      return errs;
   }
   degree_ = int(config.parameters[0]);
   SimBlock::n_params_ = degree_ + 2;

   errs = SimBlock::configDataIsOK(config);

   return errs;
}

dysysim::Sin::Sin()
   : SimBlock{"SIN", SimBlock::ioType_t::input1, 2}
   , multiplier_{1.0}
   , phase_{0.0}
{
}

std::vector<std::error_code>
dysysim::Sin::config(const SimBlock::configData_t &config)
{
   std::vector<std::error_code> errs;

   id_ = config.id;
   inputs_ = config.inputs;
   multiplier_ = config.parameters[0];
   phase_ - config.parameters[1];

   return errs;
}

std::vector<std::error_code>
dysysim::Sin::configDataIsOK(const SimBlock::configData_t &config) const
{
   auto errs = SimBlock::configDataIsOK(config);

   return errs;
}
