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

/// PI controller: out = in * (Kp + (Ki / s))
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

   /// @brief Uses Euler integration
   /// @param in PI controller error input
   void input(double in)
   {
      out_int_ += Ki_ * SimTime::delta_t * in;
      out_ = in * Kp_ + out_int_;
   }

   void reset() { out_ = 0; }

private:
   double Kp_;
   double Ki_;
   double out_int_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

/// PID controller: out = in * (Kp + (Ki / s) + Kd * s)
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
      //    _z.push_back(in);
      //    _z.pop_front();
      //    out_ = _z[0] + _K1 * _z[1] + _K2 * _z[2] + _K3 * _z[3];
      out_int_ += Ki_ * SimTime::delta_t * in;
      out_dif_ = Kd_ * (in - in_n_1_) / SimTime::delta_t;
      out_ = in * Kp_ + out_int_ + out_dif_;
      in_n_1_ = in;
   }

   void reset()
   {
      //    _z.clear();
      //    _z = {0, 0, 0, 0};
      //
   }

private:
   // const double _Kp;
   // const double _tau_I;
   // const double _tau_D;
   // const double _K1{_Kp * (1 + (1 / _tau_I) + _tau_D)};
   // const double _K2{_Kp * (1 - 2 * _tau_D)};
   // const double _K3{_Kp * _tau_D};
   // std::deque<double> _z;
   double Kp_;
   double Ki_;
   double Kd_;
   double out_int_;
   double out_dif_;
   double in_n_1_;

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
