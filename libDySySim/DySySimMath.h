#ifndef DYSYSIMMATH_H
#define DYSYSIMMATH_H

#include "ErrorCodes.h"
#include "SimBlock.h"

#include <cmath>

namespace dysysim {

class Abs : public SimBlock
{
public:
   Abs();
   ~Abs() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Abs>();
   }

   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { input(sumInputs()); }

   void input(double in) { out_ = multiplier_ * std::abs(in); }

private:
   double multiplier_;

private:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

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

   void input(double in) { out_ = std::cos(in * multiplier_ + phase_); }

private:
   double multiplier_;
   double phase_;

private:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class Polynomial : public SimBlock
{
public:
   Polynomial();
   ~Polynomial() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Polynomial>();
   }

   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { input(sumInputs()); }

   void input(double inp)
   {
      auto power = inp;
      for (auto indx = 0; auto coef : coefficients_) {
         if (indx == 0) {
            out_ = coef;
         } else {
            out_ += coef * power;
            power *= inp;
         }
         ++indx;
      }
   }

private:
   mutable int degree_;
   mutable std::vector<double> coefficients_;

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

class SquareRoot : public SimBlock
{
public:
   SquareRoot();
   ~SquareRoot() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<SquareRoot>();
   }

   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { input(sumInputs()); }

   void input(double in) { out_ = multiplier_ * std::sqrt(in); }

private:
   double multiplier_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

} // namespace dysysim

#endif
