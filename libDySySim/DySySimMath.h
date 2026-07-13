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

   size_t n_params(const configData_t &) const override { return 1; }

   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { input(sumInputs()); }

   void input(double in) { out_ = multiplier_ * std::abs(in); }

private:
   double multiplier_;
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

   size_t n_params(const configData_t &) const override { return 2; }

   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { input(sumInputs()); }

   void input(double in) { out_ = std::cos(in * multiplier_ + phase_); }

private:
   double multiplier_;
   double phase_;
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

   size_t n_params(const configData_t &config) const override
   {
      return static_cast<size_t>(config.parameters[0]) + 2;
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
   int degree_;
   std::vector<double> coefficients_;
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

   size_t n_params(const configData_t &) const override { return 2; }

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

   size_t n_params(const configData_t &) const override { return 1; }

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
