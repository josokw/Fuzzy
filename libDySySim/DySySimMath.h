#ifndef DYSYSIMMATH_H
#define DYSYSIMMATH_H

#include "ErrorCodes.h"
#include "SimBlock.h"

#define _USE_MATH_DEFINES
#include <cmath>

namespace dysysim {

class Cos : public SimBlock
{
public:
   Cos();
   ~Cos() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Cos>();
   }

   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { input(sumInputs()); }
   void input(double in) { out_ = std::cos(in * multipier_ + phase_); }

private:
   double multipier_;
   double phase_;

private:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class Sin : public SimBlock
{
public:
   Sin();
   ~Sin() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Sin>();
   }

   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { input(sumInputs()); }
   void input(double in) { out_ = std::sin(in * multiplier_ + phase_); }

private:
   double multiplier_;
   double phase_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

} // namespace dysysim

#endif
