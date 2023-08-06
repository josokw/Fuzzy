#ifndef DYSYSIMCONTROL_H
#define DYSYSIMCONTROL_H

#include "SimBlock.h"

#include <deque>

namespace dysysim {

class Hysteresis : public SimBlock
{
public:
   Hysteresis();
   ~Hysteresis() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Hysteresis>();
   }

   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { input(sumInputs()); }

   void input(double in)
   {
      if (in >= in_up_max_1_) {
         out_ = 1.0;
         up_ = false;
         return;
      }
      if (in <= in_down_min_1_) {
         out_ = -1.0;
         up_ = true;
         return;
      }

      if (up_) {
         if (in < in_up_max_1_ and in > in_up_min_1_) {
            out_ = slope_ * (in - hysteresis_);
            return;
         }
      } else {
         if (in < in_down_max_1_ and in > in_down_min_1_) {
            out_ = slope_ * (in + hysteresis_);
            return;
         }
      }
   }

   void reset() { out_ = out_t0_; }

private:
   double out_t0_;
   double hysteresis_;
   double slope_;
   // state vars
   bool up_;
   double in_up_max_1_;
   double in_up_min_1_;
   double in_down_max_1_;
   double in_down_min_1_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

/// PI controller.
/// \todo test
class PI : public SimBlock
{
public:
   PI();
   ~PI() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<PI>();
   }

   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { input(sumInputs()); }

   void input(double in)
   {
      z_.push_back(in);
      z_.pop_front();
      out_ = z_[0] + K1_ * z_[1] + K2_ * z_[2];
   }

   void reset()
   {
      z_.clear();
      z_ = {0, 0, 0};
   }

private:
   double Kp_;
   double tau_I_;
   double K1_{Kp_ * (1 + (1 / tau_I_))};
   double K2_{Kp_};
   std::deque<double> z_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

/// PID controller.
/// \todo test
class PID : public SimBlock
{
public:
   PID();
   ~PID() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<PID>();
   }

   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { input(sumInputs()); }

   void input(double in)
   {
      _z.push_back(in);
      _z.pop_front();
      out_ = _z[0] + _K1 * _z[1] + _K2 * _z[2] + _K3 * _z[3];
   }

   void reset()
   {
      _z.clear();
      _z = {0, 0, 0, 0};
   }

private:
   const double _Kp;
   const double _tau_I;
   const double _tau_D;
   const double _K1{_Kp * (1 + (1 / _tau_I) + _tau_D)};
   const double _K2{_Kp * (1 - 2 * _tau_D)};
   const double _K3{_Kp * _tau_D};
   std::deque<double> _z;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class ZeroOrderHold : public SimBlock
{
public:
   ZeroOrderHold();
   ~ZeroOrderHold() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<ZeroOrderHold>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { input(sumInputs()); }

   void input(double in) { out_ = (sample_++ % nSamples_ == 0) ? in : out_; }

private:
   const int nSamples_;
   int sample_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

} // namespace dysysim

#endif
