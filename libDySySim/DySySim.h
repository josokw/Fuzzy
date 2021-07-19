#ifndef DYSYSIM_H
#define DYSYSIM_H

#include "SimBlock.h"
#include "SimBlockIO.h"
#include "SimBlockO.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <functional>
#include <iostream>
#include <queue>

// Dynamical Systems Simulator: DySySim ===================================

namespace dysysim {

// Output blocks ----------------------------------------------------------

class Constant : public SimBlockO
{
public:
   Constant()
      : SimBlockO{}
   {
   }
   virtual ~Constant() = default;
   void config(const SimBlock::configData_t &config) override;
};

// Input output blocks ----------------------------------------------------

class AlgebraicDelay : public SimBlockIO
{
public:
   AlgebraicDelay()
      : SimBlockIO{}
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

class Attenuator : public SimBlockIO
{
public:
   Attenuator()
      : SimBlockIO{}
      , attenuation_{1.0}
   {
   }
   virtual ~Attenuator() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in) { out_ = in / attenuation_; }

private:
   double attenuation_;
};

class Cos : public SimBlockIO
{
public:
   Cos()
      : SimBlockIO{}
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

class Divider : public SimBlockIO
{
public:
   Divider()
      : SimBlockIO{}
   {
   }
   virtual ~Divider() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in1, double in2) { out_ = in1 / in2; }
};

class Gain : public SimBlockIO
{
public:
   Gain()
      : SimBlockIO{}
      , gain_(1.0)
   {
   }
   virtual ~Gain() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in) { out_ = in * gain_; }

private:
   double gain_;
};

class Limit : public SimBlockIO
{
public:
   Limit()
      : SimBlockIO{}
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

class Max : public SimBlockIO
{
public:
   Max()
      : SimBlockIO{}
   {
   }
   virtual ~Max() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in1, double in2) { out_ = in1 > in2 ? in1 : in2; }
};

class Min : public SimBlockIO
{
public:
   Min()
      : SimBlockIO{}
   {
   }
   virtual ~Min() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in1, double in2) { out_ = in1 < in2 ? in1 : in2; }
};

class Multiplier : public SimBlockIO
{
public:
   Multiplier()
      : SimBlockIO{}
   {
   }
   virtual ~Multiplier() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in1, double in2) { out_ = in1 * in2; }
};

class Sin : public SimBlockIO
{
public:
   Sin()
      : SimBlockIO{}
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

class Summator : public SimBlockIO
{
public:
   Summator()
      : SimBlockIO{}
   {
   }
   virtual ~Summator() = default;

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
class Frequency : public TimedSimBlockO
{
public:
   Frequency()
      : TimedSimBlockO{}
      , frequency_{1.0}
      , phase_{0.0}
   {
   }
   virtual ~Frequency() = default;

   void config(const SimBlock::configData_t &config) override;
   void next() { out_ = std::sin(2 * M_PI * frequency_ * SimTime::t + phase_); }

private:
   double frequency_;
   double phase_;
};

class Step : public TimedSimBlockO
{
public:
   Step()
      : TimedSimBlockO{}
      , step_out_{1.0}
      , step_t_{10}
   {
   }
   virtual ~Step() = default;

   void config(const SimBlock::configData_t &config) override;
   void next() { out_ = (SimTime::t >= step_t_) ? step_out_ : initial_out_; }

private:
   double step_out_;
   double step_t_;
};

class Puls : public TimedSimBlockO
{
public:
   Puls()
      : TimedSimBlockO{}
      , off_{0.0}
      , on_{1.0}
      , t_on_{1.0}
      , t_off_{2.0}
   {
   }
   virtual ~Puls() = default;

   void config(const SimBlock::configData_t &config) override;
   void next() { out_ = (SimTime::t >= t_on_ and SimTime::t <= t_off_) ? on_ : off_; }

private:
   double off_;
   double on_;
   double t_on_;
   double t_off_;
};

/// Every new instantiated Time object will reset the time to 0.
class Time : public TimedSimBlockO
{
public:
   Time()
      : TimedSimBlockO{}
   {
      SimTime::reset();
      SimTime::delta_t = 1.0;
   }
   virtual ~Time() = default;

   auto operator()() { return SimTime::t; }

   void config(const SimBlock::configData_t &config) override;

   void next()
   {
      SimTime::next();
      out_ = SimTime::t;
   }
};

// Timed input output blocks
// ---------------------------------------------------

class Delay : public TimedSimBlockIO
{
public:
   Delay()
      : TimedSimBlockIO{}
      , delaytime_{1.0}
      , buffer_{}
   {
      // for (int i = 0; i < int(delaytime_ / SimTime::delta_t); i++) {
      //    _buffer.push(initial_out);
      // }
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
   double delaytime_;
   std::queue<double> buffer_;
};

class FirstOrder : public TimedSimBlockIO
{
public:
   FirstOrder()
      : TimedSimBlockIO{}
      , timeConstant_{1.0}
   {
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
class Function : public SimBlockIO
{
public:
   Function()
      : SimBlockIO{}
      , callback_{cos}
   {
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

class OnOff : public SimBlockIO
{
public:
   OnOff()
      : SimBlockIO{}
      , onoff_{1.0}
      , on_{1.0}
      , off_{0.0}
   {
   }
   virtual ~OnOff() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in) { out_ = (in < onoff_) ? off_ : on_; }

private:
   const double onoff_;
   const double on_;
   const double off_;
};

/// Trapezoidal integration
class Integrator : public TimedSimBlockIO
{
public:
   Integrator()
      : TimedSimBlockIO{}
   {
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
class IntegratorEuler : public TimedSimBlockIO
{
public:
   IntegratorEuler()
      : TimedSimBlockIO{}
      , initial_out_{0.0}
   {
   }
   virtual ~IntegratorEuler() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in) { out_ += in * SimTime::delta_t; }
   void reset() { out_ = initial_out_; }

private:
   double initial_out_;
};

/// Trapezoidal integration.
class IntegratorTrapezoidal : public TimedSimBlockIO
{
public:
   IntegratorTrapezoidal()
      : TimedSimBlockIO{}
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
class PI : public TimedSimBlockIO
{
public:
   PI()
      : TimedSimBlockIO{}
      , Kp_{1.0}
      , tau_I_{1.0}
      , z_{3, 0.0}
   {
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
class PID : public TimedSimBlockIO
{
public:
   PID()
      : TimedSimBlockIO{}
      , _Kp{1.0}
      , _tau_I{1.0}
      , _tau_D{1.0}
      , _z{4, 0.0}
   {
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

class ZeroOrderHold : public TimedSimBlockIO
{
public:
   ZeroOrderHold()
      : TimedSimBlockIO{}
      , nSamples_{1}
      , sample_{0}
   {
   }
   virtual ~ZeroOrderHold() = default;

   void config(const SimBlock::configData_t &config) override;
   void input(double in) { out_ = (sample_++ % nSamples_ == 0) ? in : out_; }

private:
   const int nSamples_;
   int sample_;
};

} // namespace dysysim

#endif // DYSYSIM_H
