#ifndef DYSYSIM_H
#define DYSYSIM_H

#include "DySySimHC.h"
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
   Constant();
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
   AlgebraicDelay();
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

private:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class Attenuator : public SimBlock
{
public:
   Attenuator();
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

class Divider : public SimBlock
{
public:
   Divider();
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
   Gain();
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
   Limit();
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
   Max();
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
   Min();
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
   Multiplier();
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

class Offset : public SimBlock
{
public:
   Offset();
   ~Offset() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Offset>();
   }

   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { out_ = scale_ * (sumInputs() + delta_); }

private:
   double scale_;
   double delta_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class Summator : public SimBlock
{
public:
   Summator();
   ~Summator() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Summator>();
   }

   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { out_ = sumInputs(); }

private:
   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

/// Sinus generator, amplitude = 1
class Frequency : public SimBlock
{
public:
   Frequency();
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
   Step();
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
   Puls();
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
   Time();
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
   Delay();
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
   FirstOrder();
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

template <typename T>
class Function : public SimBlock
{
public:
   Function()
      : SimBlock{"FNC", SimBlock::ioType_t::input1N}
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
   OnOff();
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
   Integrator();
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
   IntegratorEuler();
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

/// Writes input data to stdout.
class Log : public SimBlock
{
public:
   Log();
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
   Relay();
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

class SecondOrder : public SimBlock
{
public:
   SecondOrder();
   ~SecondOrder() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<SecondOrder>();
   }

   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;

   void exe() override { input(sumInputs()); }

   void input(double in)
   {
      out_ = int_3_.output();
      int_3_[0] = int_2_.output();

      int_2_[0] =
         (in - (gain_4_ * int_2_.output()) - int_3_.output()) * gain_1_;

      int_2_.exe();
      int_3_.exe();
   }

private:
   double w_res_;
   double damping_;

   double gain_1_;
   IntegratorHC int_2_;
   IntegratorHC int_3_;
   double gain_4_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

class Sign : public SimBlock
{
public:
   Sign();
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
   Clock();
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
