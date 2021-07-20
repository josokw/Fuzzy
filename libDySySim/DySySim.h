#ifndef DYSYSIM_H
#define DYSYSIM_H

#include "SimBlock.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <functional>
#include <iostream>
#include <queue>

// Dynamical Systems Simulator: DySySim ===================================

namespace dysysim {

// Output blocks ----------------------------------------------------------

class Constant : public SimBlock
{
public:
   Constant()
      : SimBlock{}
   {
   }
   ~Constant() override = default;
   void config(const SimBlock::configData_t &config) override;
};

class AlgebraicDelay : public SimBlock
{
public:
   AlgebraicDelay()
      : SimBlock{}
      , out_previous_{0.0}
   {
   }
   virtual ~AlgebraicDelay() = default;

   void config(const SimBlock::configData_t &config) override;

   void input(double in)
   {
      out_ = out_previous_;
      out_previous_ = in;
   }

private:
   double out_previous_;
};

class Attenuator : public SimBlock
{
public:
   Attenuator()
      : SimBlock{}
      , attenuation_{1.0}
   {
   }
   virtual ~Attenuator() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in) { out_ = in / attenuation_; }

private:
   double attenuation_;
};

class Cos : public SimBlock
{
public:
   Cos()
      : SimBlock{}
      , multipier_{1.0}
      , phase_{0.0}
   {
   }
   virtual ~Cos() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in) { out_ = std::cos(in * multipier_ + phase_); }

private:
   double multipier_;
   double phase_;
};

class Divider : public SimBlock
{
public:
   Divider()
      : SimBlock{}
   {
   }
   virtual ~Divider() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in1, double in2) { out_ = in1 / in2; }
};

class Gain : public SimBlock
{
public:
   Gain()
      : SimBlock{}
      , gain_(1.0)
   {
   }
   virtual ~Gain() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in) { out_ = in * gain_; }

private:
   double gain_;
};

class Limit : public SimBlock
{
public:
   Limit()
      : SimBlock{}
      , min_(-1.0)
      , max_(1.0)
   {
   }
   virtual ~Limit() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in) { out_ = std::min(std::max(min_, in), max_); }

private:
   double min_;
   double max_;
};

class Max : public SimBlock
{
public:
   Max()
      : SimBlock{}
   {
   }
   virtual ~Max() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in1, double in2) { out_ = in1 > in2 ? in1 : in2; }
};

class Min : public SimBlock
{
public:
   Min()
      : SimBlock{}
   {
   }
   virtual ~Min() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in1, double in2) { out_ = in1 < in2 ? in1 : in2; }
};

class Multiplier : public SimBlock
{
public:
   Multiplier()
      : SimBlock{}
   {
   }
   virtual ~Multiplier() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in1, double in2) { out_ = in1 * in2; }
};

class Sin : public SimBlock
{
public:
   Sin()
      : SimBlock{}
      , multiplier_{1.0}
      , phase_{0.0}
   {
   }
   virtual ~Sin() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in) { out_ = std::sin(in * multiplier_ + phase_); }

private:
   double multiplier_;
   double phase_;
};

class Summator : public SimBlock
{
public:
   Summator()
      : SimBlock{}
   {
   }
   ~Summator() override = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in1, double in2) { out_ = in1 + in2; }
   void input(double in1, double in2, double in3) { out_ = in1 + in2 + in3; }
   void input(double in1, double in2, double in3, double in4)
   {
      out_ = in1 + in2 + in3 + in4;
   }
};

// Timed output blocks
// ---------------------------------------------------------

// Sinus generator, amplitude = 1
class Frequency : public SimBlock
{
public:
   Frequency()
      : SimBlock{}
      , frequency_{1.0}
      , phase_{0.0}
   {
      blockType_ = "FRQ";
   }
   virtual ~Frequency() = default;

   void config(const SimBlock::configData_t &config) override;
   void next() { out_ = std::sin(2 * M_PI * frequency_ * SimTime::t + phase_); }

private:
   double frequency_;
   double phase_;
};

class Step : public SimBlock
{
public:
   Step()
      : SimBlock{}
      , off_{0.0}
      , on_{1.0}
      , t_on_{1.0}
   {
      blockType_ = "STP";
   }
   virtual ~Step() = default;

   void config(const SimBlock::configData_t &config) override;
   void exe() { out_ = (SimTime::t < t_on_) ? off_ : on_; }

private:
   double off_;
   double on_;
   double t_on_;
};

class Puls : public SimBlock
{
public:
   Puls()
      : SimBlock{}
      , off_{0.0}
      , on_{1.0}
      , t_on_{1.0}
      , t_off_{2.0}
   {
      blockType_ = "PLS";
   }
   virtual ~Puls() = default;

   void config(const SimBlock::configData_t &config) override;
   void exe()
   {
      out_ = (SimTime::t >= t_on_ and SimTime::t < t_off_) ? on_ : off_;
   }

private:
   double off_;
   double on_;
   double t_on_;
   double t_off_;
};

/// Every new instantiated Time object will reset the time to 0.
class Time : public SimBlock
{
public:
   Time()
      : SimBlock{}
   {
      SimTime::reset();
      SimTime::delta_t = 1.0;
      blockType_ = "TIME";
   }
   ~Time() override = default;

   auto operator()() { return SimTime::t; }
   void config(const SimBlock::configData_t &config) override;

   void exe()
   {
      SimTime::next();
      out_ = SimTime::t;
   }
};

// Timed input output blocks
// ---------------------------------------------------

class Delay : public SimBlock
{
public:
   Delay()
      : SimBlock{}
      , out_t0_{0.0}
      , delaytime_{1.0}
      , buffer_{}
   {
      blockType_ = "DLY";
   }
   virtual ~Delay() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in)
   {
      buffer_.push(in);
      out_ = buffer_.front();
      buffer_.pop();
   }

private:
   double out_t0_;
   double delaytime_;
   std::queue<double> buffer_;
};

class FirstOrder : public SimBlock
{
public:
   FirstOrder()
      : SimBlock{}
      , timeConstant_{1.0}
   {
      blockType_ = "FIO";
   }
   ~FirstOrder() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in)
   {
      out_ += SimTime::delta_t * (in - out_) / timeConstant_;
   }

private:
   double timeConstant_;
};

/// \todo Implement setter for callback_
template <typename T>
class Function : public SimBlock
{
public:
   Function()
      : SimBlock{}
      , callback_{cos}
   {
      blockType_ = "FNC";
   }
   virtual ~Function() = default;

   void config(const SimBlock::configData_t &config) override;
   void setFunction(std::function<double(T)> cbf) { callback_ = cbf; }
   void input(double in) { out_ = callback_(in); }

private:
   std::function<double(T)> callback_;
};

template <typename T>
void dysysim::Function<T>::config(const SimBlock::configData_t &config)
{
   id_ = config.id;
   inputs_ = config.inputs;
   if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
      SimBlock::allSimBlocks_s[id_] = this;
   }
}

/// OnOff starts (t == 0) off.
/// \todo Add hysteresis
class OnOff : public SimBlock
{
public:
   OnOff()
      : SimBlock{}
      , off_{0.0}
      , on_{1.0}
      , onoff_{1.0}
   {
      blockType_ = "ONOFF";
   }
   ~OnOff() override = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in) { out_ = (in < onoff_) ? off_ : on_; }

private:
   double off_;
   double on_;
   double onoff_;
};

/// Trapezoidal integration
class Integrator : public SimBlock
{
public:
   Integrator()
      : SimBlock{}
   {
      blockType_ = "INT";
   }
   virtual ~Integrator() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in)
   {
      out_ += 0.5 * (in + in_previous) * SimTime::delta_t;
      in_previous = in;
   }
   void reset() { out_ = initial_out_; }

private:
   double initial_out_{0.0};
   double in_previous = initial_out_;
};

/// Forward Euler integration
class IntegratorEuler : public SimBlock
{
public:
   IntegratorEuler()
      : SimBlock{}
      , initial_out_{0.0}
   {
      blockType_ = "EUL";
   }
   virtual ~IntegratorEuler() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in) { out_ += in * SimTime::delta_t; }
   void reset() { out_ = initial_out_; }

private:
   double initial_out_;
};

/// Trapezoidal integration.
class IntegratorTrapezoidal : public SimBlock
{
public:
   IntegratorTrapezoidal()
      : SimBlock{}
      , initial_out_{0.0}
      , in_previous_{0}
   {
   }
   virtual ~IntegratorTrapezoidal() = default;
   void config(const SimBlock::configData_t &config) override;
   void input(double in)
   {
      out_ += 0.5 * (in + in_previous_) * SimTime::delta_t;
      in_previous_ = in;
   }
   void reset()
   {
      out_ = initial_out_;
      in_previous_ = 0.0;
   }

private:
   double initial_out_;
   double in_previous_;
};

// @TBD not tested
class PI : public SimBlock
{
public:
   PI()
      : SimBlock{}
      , Kp_{1.0}
      , tau_I_{1.0}
      , z_{3, 0.0}
   {
      blockType_ = "PI";
   }
   virtual ~PI() = default;

   void config(const SimBlock::configData_t &config) override;
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
};

// @TBD not tested
class PID : public SimBlock
{
public:
   PID()
      : SimBlock{}
      , _Kp{1.0}
      , _tau_I{1.0}
      , _tau_D{1.0}
      , _z{4, 0.0}
   {
      blockType_ = "PID";
   }
   virtual ~PID() = default;

   void config(const SimBlock::configData_t &config) override;
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
};

class ZeroOrderHold : public SimBlock
{
public:
   ZeroOrderHold()
      : SimBlock{}
      , nSamples_{1}
      , sample_{0}
   {
      blockType_ = "ZOH";
   }
   virtual ~ZeroOrderHold() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in) { out_ = (sample_++ % nSamples_ == 0) ? in : out_; }

private:
   const int nSamples_;
   int sample_;
};

class Log : public SimBlock
{
public:
   Log()
      : SimBlock{}
   {
      blockType_ = "LOG";
   }

   void config(const SimBlock::configData_t &config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) == end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }

   void exe() override
   {
      for (auto id : inputs_) {
         auto pSB = SimBlock::getSimBlock(id);
         std::cerr << " t = " << SimBlock::getSimBlock(1)->output() << "   ";
         if (id != 1) {
            std::cerr << id << " " << pSB->getBlockType() << " = "
                      << pSB->output() << "\n";
         }
      }
   }
};

} // namespace dysysim

#endif // DYSYSIM_H
