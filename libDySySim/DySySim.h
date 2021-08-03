#ifndef DYSYSIM_H
#define DYSYSIM_H

#include "SimBlock.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <functional>
#include <iostream>
#include <queue>

namespace dysysim {

class Constant : public SimBlock
{
public:
   Constant()
      : SimBlock{"CON", SimBlock::ioType_t::input0}
   {
   }
   ~Constant() override = default;

   SimBlock *create() override { return new Constant; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}

protected:
   bool configDataIsOK(const SimBlock::configData_t &config) const override;
};

class AlgebraicDelay : public SimBlock
{
public:
   AlgebraicDelay()
      : SimBlock{"ADL", SimBlock::ioType_t::history}
      , out_previous_{0.0}
   {
   }
   ~AlgebraicDelay() override = default;

   SimBlock *create() override { return new AlgebraicDelay; }
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
      : SimBlock{"ATT", SimBlock::ioType_t::inputoutput}
      , attenuation_{1.0}
   {
   }
   ~Attenuator() override = default;

   SimBlock *create() override { return new Attenuator; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}
   void input(double in) { out_ = in / attenuation_; }

protected:
   bool configDataIsOK(const SimBlock::configData_t &config) const override;

private:
   double attenuation_;
};

class Cos : public SimBlock
{
public:
   Cos()
      : SimBlock{"COS", SimBlock::ioType_t::inputoutput}
      , multipier_{1.0}
      , phase_{0.0}
   {
   }
   ~Cos() override = default;

   SimBlock *create() override { return new Cos; }
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
      : SimBlock{"DIV", SimBlock::ioType_t::inputoutput}
   {
   }
   ~Divider() override = default;

   SimBlock *create() override { return new Divider; }
   void config(const SimBlock::configData_t &config) override;
   void input(double in1, double in2) { out_ = in1 / in2; }
};

class Gain : public SimBlock
{
public:
   Gain()
      : SimBlock{"GAIN", SimBlock::ioType_t::inputoutput}
      , gain_(1.0)
   {
   }
   ~Gain() override = default;

   SimBlock *create() override { return new Gain; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}
   void input(double in) { out_ = in * gain_; }

private:
   double gain_;
};

class Limit : public SimBlock
{
public:
   Limit()
      : SimBlock{"LIM", SimBlock::ioType_t::inputoutput}
      , min_(-1.0)
      , max_(1.0)
   {
   }
   ~Limit() override = default;

   SimBlock *create() override { return new Limit; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}
   void input(double in) { out_ = std::min(std::max(min_, in), max_); }

private:
   double min_;
   double max_;
};

class Max : public SimBlock
{
public:
   Max()
      : SimBlock{"MAX", SimBlock::ioType_t::inputoutput}
   {
   }
   ~Max() override = default;

   SimBlock *create() override { return new Max; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}
   void input(double in1, double in2) { out_ = in1 > in2 ? in1 : in2; }
};

class Min : public SimBlock
{
public:
   Min()
      : SimBlock{"MIN", SimBlock::ioType_t::inputoutput}
   {
   }
   ~Min() override = default;

   SimBlock *create() override { return new Min; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}
   void input(double in1, double in2) { out_ = in1 < in2 ? in1 : in2; }
};

class Multiplier : public SimBlock
{
public:
   Multiplier()
      : SimBlock{"MUL", SimBlock::ioType_t::inputoutput}
   {
   }
   ~Multiplier() override = default;

   SimBlock *create() override { return new Multiplier; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}
   void input(double in1, double in2) { out_ = in1 * in2; }
};

class Sin : public SimBlock
{
public:
   Sin()
      : SimBlock{"SIN", SimBlock::ioType_t::inputoutput}
      , multiplier_{1.0}
      , phase_{0.0}
   {
   }
   ~Sin() override = default;

   SimBlock *create() override { return new Sin; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}
   void input(double in) { out_ = std::sin(in * multiplier_ + phase_); }

private:
   double multiplier_;
   double phase_;
};

class Summator : public SimBlock
{
public:
   Summator()
      : SimBlock{"SUM", SimBlock::ioType_t::inputoutput}
   {
   }
   ~Summator() override = default;

   SimBlock *create() override { return new Summator; }
   void config(const SimBlock::configData_t &config) override;
   bool configDataIsOK(const SimBlock::configData_t &config) const override;
   void exe() override {}
   void input(double in1, double in2) { out_ = in1 + in2; }
   void input(double in1, double in2, double in3) { out_ = in1 + in2 + in3; }
   void input(double in1, double in2, double in3, double in4)
   {
      out_ = in1 + in2 + in3 + in4;
   }
};

/// Sinus generator, amplitude = 1
class Frequency : public SimBlock
{
public:
   Frequency()
      : SimBlock{"FRQ", SimBlock::ioType_t::input0}
      , frequency_{1.0}
      , phase_{0.0}
   {
   }
   ~Frequency() override = default;

   SimBlock *create() override { return new Frequency; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}
   void next() { out_ = std::sin(2 * M_PI * frequency_ * SimTime::t + phase_); }

private:
   double frequency_;
   double phase_;
};

class Step : public SimBlock
{
public:
   Step()
      : SimBlock{"STP", SimBlock::ioType_t::input0}
      , off_{0.0}
      , on_{1.0}
      , t_on_{1.0}
   {
   }
   ~Step() override = default;

   SimBlock *create() override { return new Step; }
   void config(const SimBlock::configData_t &config) override;
   bool configDataIsOK(const SimBlock::configData_t &config) const override;
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
      : SimBlock{"PLS", SimBlock::ioType_t::input0}
      , off_{0.0}
      , on_{1.0}
      , t_on_{1.0}
      , t_off_{2.0}
   {
   }
   ~Puls() override = default;

   SimBlock *create() override { return new Puls; }
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
      : SimBlock{"TIME", SimBlock::ioType_t::input0}
   {
   }
   ~Time() override = default;

   SimBlock *create() override { return new Time; }
   void config(const SimBlock::configData_t &config) override;
   bool configDataIsOK(const SimBlock::configData_t &config) const override;
   void exe() override { out_ = SimTime::t; }
};

class Delay : public SimBlock
{
public:
   Delay()
      : SimBlock{"DLY", SimBlock::ioType_t::history}
      , out_t0_{0.0}
      , delaytime_{1.0}
      , buffer_{}
   {
   }
   ~Delay() override = default;

   SimBlock *create() override { return new Delay; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}
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
      : SimBlock{"FIO", SimBlock::ioType_t::history}
      , timeConstant_{1.0}
   {
   }
   ~FirstOrder() override = default;

   SimBlock *create() override { return new FirstOrder; }
   void config(const SimBlock::configData_t &config) override;
   bool configDataIsOK(const SimBlock::configData_t &config) const override;
   void exe() override {}
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
      : SimBlock{"FNC", SimBlock::ioType_t::inputoutput}
      , callback_{cos}
   {
   }
   ~Function() override = default;

   SimBlock *create() override { return new Function<T>; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}

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
      : SimBlock{"ONOFF", SimBlock::ioType_t::inputoutput}
      , off_{0.0}
      , on_{1.0}
      , onoff_{1.0}
   {
   }
   ~OnOff() override = default;

   SimBlock *create() override { return new OnOff; }
   void config(const SimBlock::configData_t &config) override;
   bool configDataIsOK(const SimBlock::configData_t &config) const override;
   void exe() override {}
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
      : SimBlock{"INT", SimBlock::ioType_t::history}
   {
   }
   ~Integrator() override = default;

   SimBlock *create() override { return new Integrator; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}
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
      : SimBlock{"EUL", SimBlock::ioType_t::history}
      , initial_out_{0.0}
   {
   }
   ~IntegratorEuler() override = default;

   SimBlock *create() override { return new IntegratorEuler; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}
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
      : SimBlock{"TPZD", SimBlock::ioType_t::history}
      , initial_out_{0.0}
      , in_previous_{0}
   {
   }
   ~IntegratorTrapezoidal() override = default;

   SimBlock *create() override { return new IntegratorTrapezoidal; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}
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

/// PI controller.
/// \todo test
class PI : public SimBlock
{
public:
   PI()
      : SimBlock{"PI", SimBlock::ioType_t::history}
      , Kp_{1.0}
      , tau_I_{1.0}
      , z_{3, 0.0}
   {
   }
   ~PI() override = default;

   SimBlock *create() override { return new PI; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}
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

/// PID controller.
/// \todo test
class PID : public SimBlock
{
public:
   PID()
      : SimBlock{"PID", SimBlock::ioType_t::history}
      , _Kp{1.0}
      , _tau_I{1.0}
      , _tau_D{1.0}
      , _z{4, 0.0}
   {
   }
   ~PID() override = default;

   SimBlock *create() override { return new PID; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}
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
      : SimBlock{"ZOH", SimBlock::ioType_t::history}
      , nSamples_{1}
      , sample_{0}
   {
   }
   ~ZeroOrderHold() override = default;

   SimBlock *create() override { return new ZeroOrderHold; }
   void config(const SimBlock::configData_t &config) override;
   void exe() override {}
   void input(double in) { out_ = (sample_++ % nSamples_ == 0) ? in : out_; }

private:
   const int nSamples_;
   int sample_;
};

/// Writes input data to stdout.
class Log : public SimBlock
{
public:
   Log()
      : SimBlock{"LOG", SimBlock::ioType_t::output0}
   {
   }
   ~Log() override = default;

   SimBlock *create() override { return new Log; }
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
      std::cerr << " t = " << SimTime::t << "   ";
      for (auto id : inputs_) {
         auto pSB = SimBlock::getSimBlock(id);
         std::cerr << id << " " << pSB->getBlockType() << " = " << pSB->output()
                   << "  ";
      }
      std::cerr << "\n";
   }
};

} // namespace dysysim

#endif // DYSYSIM_H
