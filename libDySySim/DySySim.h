#ifndef DYSYSIM_H
#define DYSYSIM_H

#include "ErrorCodes.h"
#include "SimBlock.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

namespace dysysim {

class Constant : public SimBlock
{
public:
   Constant()
      : SimBlock{"CON", SimBlock::ioType_t::input0}
   {
   }
   ~Constant() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Constant>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override {}

protected:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
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

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<AlgebraicDelay>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { input(sumInputs()); }
   void input(double in)
   {
      out_ = out_previous_;
      out_previous_ = in;
   }

private:
   double out_previous_;
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
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

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Attenuator>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override { input(sumInputs()); }
   void input(double in) { out_ = in / attenuation_; }

protected:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;

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

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Cos>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void input(double in) { out_ = std::cos(in * multipier_ + phase_); }

private:
   double multipier_;
   double phase_;
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class Divider : public SimBlock
{
public:
   Divider()
      : SimBlock{"DIV", SimBlock::ioType_t::inputoutput}
   {
   }
   ~Divider() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Divider>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void input(double in1, double in2) { out_ = in1 / in2; }

private:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
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

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Gain>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override { input(sumInputs()); }
   void input(double in) { out_ = in * gain_; }

private:
   double gain_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
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

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Limit>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override { input(sumInputs()); }
   void input(double in) { out_ = std::min(std::max(min_, in), max_); }

private:
   double min_;
   double max_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class Max : public SimBlock
{
public:
   Max()
      : SimBlock{"MAX", SimBlock::ioType_t::inputoutput}
   {
   }
   ~Max() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Max>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override
   {
      input(SimBlock::allSimBlocks_s[inputs_[0]]->output(),
            SimBlock::allSimBlocks_s[inputs_[1]]->output());
   }
   void input(double in1, double in2) { out_ = in1 > in2 ? in1 : in2; }

private:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class Min : public SimBlock
{
public:
   Min()
      : SimBlock{"MIN", SimBlock::ioType_t::inputoutput}
   {
   }
   ~Min() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Min>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override
   {
      input(SimBlock::allSimBlocks_s[inputs_[0]]->output(),
            SimBlock::allSimBlocks_s[inputs_[1]]->output());
   }
   void input(double in1, double in2) { out_ = in1 < in2 ? in1 : in2; }

private:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class Multiplier : public SimBlock
{
public:
   Multiplier()
      : SimBlock{"MUL", SimBlock::ioType_t::inputoutput}
   {
   }
   ~Multiplier() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Multiplier>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override
   {
      input(SimBlock::allSimBlocks_s[inputs_[0]]->output(),
            SimBlock::allSimBlocks_s[inputs_[1]]->output());
   }
   void input(double in1, double in2) { out_ = in1 * in2; }

private:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
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

class Summator : public SimBlock
{
public:
   Summator()
      : SimBlock{"SUM", SimBlock::ioType_t::inputoutput}
   {
   }
   ~Summator() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Summator>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override { out_ = sumInputs(); }
   // void input(double in1, double in2) { out_ = in1 + in2; }
   // void input(double in1, double in2, double in3) { out_ = in1 + in2 + in3; }
   // void input(double in1, double in2, double in3, double in4)
   // {
   //    out_ = in1 + in2 + in3 + in4;
   // }

private:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
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

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Frequency>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override
   {
      out_ = std::sin(2 * M_PI * frequency_ * SimTime::t + phase_);
   }

private:
   double frequency_;
   double phase_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
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

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Step>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() { out_ = (SimTime::t < t_on_) ? off_ : on_; }

private:
   double off_;
   double on_;
   double t_on_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
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

   std::shared_ptr<SimBlock> create() override
   {
      auto p = std::make_shared<Puls>();
      return p;
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override
   {
      out_ = (SimTime::t >= t_on_ and SimTime::t < t_off_) ? on_ : off_;
   }

private:
   double off_;
   double on_;
   double t_on_;
   double t_off_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
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

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Time>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override { out_ = SimTime::t; }

private:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
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

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Delay>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override { input(sumInputs()); }
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

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
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

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<FirstOrder>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override { input(sumInputs()); }
   void input(double in)
   {
      out_ += SimTime::delta_t * (in - out_) / timeConstant_;
   }

private:
   double timeConstant_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
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

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Function<T>>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override { input(sumInputs()); }

   void setFunction(std::function<double(T)> cbf) { callback_ = cbf; }
   void input(double in) { out_ = callback_(in); }

private:
   std::function<double(T)> callback_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override
   {
      auto errs = SimBlock::configDataIsOK(config);
      if (config.inputs.size() < 1) {
         errs.push_back(SimBlockErrc::ConfigInputIdError);
         std::cerr << "---- DySySim error: should have >= 1 input\n";
      }
      return errs;
   }
};

template <typename T>
std::vector<std::error_code>
dysysim::Function<T>::config(const SimBlock::configData_t &config)
{
   auto errs = configDataIsOK(config);
   if (errs.empty()) {
      id_ = config.id;
      inputs_ = config.inputs;
   }
   return errs;
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

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<OnOff>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override { input(sumInputs()); }
   void input(double in) { out_ = (in < onoff_) ? off_ : on_; }

private:
   double off_;
   double on_;
   double onoff_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
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

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Integrator>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override { input(sumInputs()); }
   void input(double in)
   {
      out_ += 0.5 * (in + in_previous) * SimTime::delta_t;
      in_previous = in;
   }
   void reset() { out_ = initial_out_; }

private:
   double initial_out_{0.0};
   double in_previous{initial_out_};

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
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

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<IntegratorEuler>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override { input(sumInputs()); }
   void input(double in) { out_ += in * SimTime::delta_t; }
   void reset() { out_ = initial_out_; }

private:
   double initial_out_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
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
   PID()
      : SimBlock{"PID", SimBlock::ioType_t::history}
      , _Kp{1.0}
      , _tau_I{1.0}
      , _tau_D{1.0}
      , _z{4, 0.0}
   {
   }
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
   ZeroOrderHold()
      : SimBlock{"ZOH", SimBlock::ioType_t::history}
      , nSamples_{1}
      , sample_{0}
   {
   }
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

/// Writes input data to stdout.
class Log : public SimBlock
{
public:
   Log()
      : SimBlock{"LOG", SimBlock::ioType_t::output0}
   {
   }
   ~Log() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Log>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override
   {
      if (write_columns_) {
         std::cerr << '#' << std::setw(SimBlock::sim_time.width_t - 1)
                   << std::right << "t";
         for (auto index = 0; auto id : inputs_) {
            auto pSB = SimBlock::getSimBlock(id);
            // std::cerr << std::setw(2) << id << " " << std::setw(4)
            //           << pSB->getBlockType() << "  ";
            std::cerr << ' ' << std::setw(parameters_[index]) << id;
            index += 2;
         }
         std::cerr << "\n";
         write_columns_ = false;
      }
      std::cerr << std::fixed << std::right
                << std::setw(SimBlock::sim_time.width_t)
                << std::setprecision(SimBlock::sim_time.precision_t)
                << SimTime::t;
      for (auto index = 0; auto id : inputs_) {
         auto pSB = SimBlock::getSimBlock(id);
         std::cerr << ' ' << std::setw(parameters_[index])
                   << std::setprecision(parameters_[index + 1])
                   << pSB->output();
         index += 2;
      }
      std::cerr << "\n";
   }

private:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;

private:
   bool write_columns_ = true;
   std::vector<int> parameters_;
};

// Relay
class Relay : public SimBlock
{
public:
   Relay()
      : SimBlock{"RELAY", SimBlock::ioType_t::inputoutput}
      , ref_{0.0}
   {
   }
   ~Relay() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Relay>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override
   {
      input(SimBlock::allSimBlocks_s[inputs_[0]]->output(),
            SimBlock::allSimBlocks_s[inputs_[1]]->output(),
            SimBlock::allSimBlocks_s[inputs_[2]]->output());
   }
   void input(double in1, double in2, double in3)
   {
      out_ = (in1 <= ref_) ? in2 : in3;
   }

private:
   double ref_;

private:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class And : public SimBlock
{
public:
   And()
      : SimBlock{"AND", SimBlock::ioType_t::inputoutput}
   {
   }
   ~And() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<And>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { out_ = andInputs(); }

private:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class Or : public SimBlock
{
public:
   Or()
      : SimBlock{"OR", SimBlock::ioType_t::inputoutput}
   {
   }
   ~Or() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Or>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { out_ = orInputs(); }

private:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class Not : public SimBlock
{
public:
   Not()
      : SimBlock{"NOT", SimBlock::ioType_t::inputoutput}
   {
   }
   ~Not() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Not>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { out_ = notInput(); }

private:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class NAnd : public SimBlock
{
public:
   NAnd()
      : SimBlock{"NAND", SimBlock::ioType_t::inputoutput}
   {
   }
   ~NAnd() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<NAnd>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { out_ = is_0(andInputs() ? 1.0 : 0.0); }

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class NOr : public SimBlock
{
public:
   NOr()
      : SimBlock{"NOR", SimBlock::ioType_t::inputoutput}
   {
   }
   ~NOr() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<NOr>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { out_ = is_0(orInputs() ? 1.0 : 0.0); }

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class XOr : public SimBlock
{
public:
   XOr()
      : SimBlock{"XOR", SimBlock::ioType_t::inputoutput}
   {
   }
   ~XOr() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<XOr>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override
   {
      auto nand = is_0(andInputs());
      out_ = convert01(nand and orInputs());
   }

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class Sign : public SimBlock
{
public:
   Sign()
      : SimBlock{"SGN", SimBlock::ioType_t::inputoutput}
   {
   }
   ~Sign() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Sign>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { out_ = std::signbit(inputs_[0]) ? 1.0 : 0.0; }

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class Clock : public SimBlock
{
public:
   Clock()
      : SimBlock{"CLK", SimBlock::ioType_t::input0}
      , frequency_{1.0}
   {
      // out_ = 1.0;
   }
   ~Clock() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Clock>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override
   {
      out_ =
         std::signbit(std::sin(2 * M_PI * frequency_ * SimTime::t)) ? 0.0 : 1.0;
   }

private:
   double frequency_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

} // namespace dysysim

#endif // DYSYSIM_H
