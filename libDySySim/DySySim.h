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

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
      out_ = *begin(config.parameters);
   }
};

// Input output blocks ----------------------------------------------------

class AlgebraicDelay : public SimBlockIO
{
public:
   AlgebraicDelay()
      : SimBlockIO{}
      , out_previous_{initValue}
   {
   }
   virtual ~AlgebraicDelay() = default;

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }

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
   
   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
      attenuation_ = *begin(config.parameters);
   }
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

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }

   }

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

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }
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

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }

   void input(double in) { out_ = in * gain_; }

private:
   const double gain_;
};

class Limit : public SimBlockIO
{
public:
   Limit(int id, double min, double max)
      : SimBlockIO{id}
      , _min(min)
      , _max(max)
   {
   }
   virtual ~Limit() = default;

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }
   void input(double in) { _out = std::min(std::max(_min, in), _max); }

private:
   const double _min;
   const double _max;
};

class Max : public SimBlockIO
{
public:
   Max(int id)
      : SimBlockIO{id}
   {
   }
   virtual ~Max() = default;

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }
   void input(double in1, double in2) { _out = in1 > in2 ? in1 : in2; }
};

class Min : public SimBlockIO
{
public:
   Min(int id)
      : SimBlockIO{id}
   {
   }
   virtual ~Min() = default;

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }

   void input(double in1, double in2) { _out = in1 < in2 ? in1 : in2; }
};

class Multiplier : public SimBlockIO
{
public:
   Multiplier(int id)
      : SimBlockIO{id}
   {
   }
   virtual ~Multiplier() = default;

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }

   void input(double in1, double in2) { _out = in1 * in2; }
};

class Sin : public SimBlockIO
{
public:
   Sin(int id, double multiplier = 1.0, double phase = 0.0)
      : SimBlockIO{id}
      , _multiplier{multiplier}
      , _phase{phase}
   {
   }
   virtual ~Sin() = default;
   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }
   void input(double in) { _out = std::sin(in * _multiplier + _phase); }

private:
   const double _multiplier;
   const double _phase;
};

class Summator : public SimBlockIO
{
public:
   Summator()
      : SimBlockIO{}
   {
   }
   virtual ~Summator() = default;

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }

   void input(double in1, double in2) { _out = in1 + in2; }
   void input(double in1, double in2, double in3) { _out = in1 + in2 + in3; }
   void input(double in1, double in2, double in3, double in4)
   {
      _out = in1 + in2 + in3 + in4;
   }
};

// Timed output blocks
// ---------------------------------------------------------

// Sinus generator, amplitude = 1
class Frequency : public TimedSimBlockO
{
public:
   Frequency(int id, double frequency, double phase = 0.0)
      : TimedSimBlockO{id}
      , _frequency{frequency}
      , _phase{phase}
   {
   }
   virtual ~Frequency() = default;

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }

   void next() { _out = std::sin(2 * M_PI * _frequency * SimTime::t + _phase); }

private:
   const double _frequency;
   const double _phase;
};

class Step : public TimedSimBlockO
{
public:
   Step(int id, double initial_out, double step_out, double step_t)
      : TimedSimBlockO{id, initial_out}
      , _step_out{step_out}
      , _step_t{step_t}
   {
   }
   virtual ~Step() = default;

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }

   void next() { _out = (SimTime::t >= _step_t) ? _step_out : _initial_out; }

private:
   const double _step_out;
   const double _step_t;
};

/// Every new instantiated Time object will reset the time to 0.
class Time : public TimedSimBlockO
{
public:
   Time(int id, double delta_t)
      : TimedSimBlockO{id}
   {
      SimTime::reset();
      SimTime::delta_t = delta_t;
   }
   virtual ~Time() = default;

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }

   void next()
   {
      SimTime::next();
      _out = SimTime::t;
   }
};

// Timed input output blocks
// ---------------------------------------------------

class Delay : public TimedSimBlockIO
{
public:
   Delay(int id, double delaytime, double initial_out)
      : TimedSimBlockIO{id, initial_out}
      , _delaytime{delaytime}
      , _buffer{}
   {
      for (int i = 0; i < int(delaytime / SimTime::delta_t); i++) {
         _buffer.push(initial_out);
      }
   }
   virtual ~Delay() = default;

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }

   void input(double in)
   {
      _buffer.push(in);
      _out = _buffer.front();
      _buffer.pop();
   }

private:
   const double _delaytime;
   std::queue<double> _buffer;
};

class FirstOrder : public TimedSimBlockIO
{
public:
   FirstOrder(int id, double timeConstant, double initial_out = 0.0)
      : TimedSimBlockIO{id, initial_out}
      , _timeConstant{timeConstant}
   {
   }
   ~FirstOrder() = default;
   void input(double in)
   {
      _out += SimTime::delta_t * (in - _out) / _timeConstant;
   }

private:
   const double _timeConstant;
};

template <typename T>
class Function : public SimBlockIO
{
public:
   Function(int id, std::function<double(T)> callback)
      : SimBlockIO{id}
      , _callback{callback}
   {
   }
   virtual ~Function() = default;

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }

   void input(double in) { _out = _callback(in); }

private:
   std::function<double(T)> _callback;
};

class OnOff : public SimBlockIO
{
public:
   OnOff(int id, double onoff, double on, double off)
      : SimBlockIO{id}
      , _onoff{onoff}
      , _on(on)
      , _off{off}
   {
   }
   virtual ~OnOff() = default;
   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }

   void input(double in) { _out = (in < _onoff) ? _off : _on; }

private:
   const double _onoff;
   const double _on;
   const double _off;
};

// Trapezoidal integration
class Integrator : public TimedSimBlockIO
{
public:
   Integrator(int id, double initial_out = 0)
      : TimedSimBlockIO{id, initial_out}
   {
   }
   virtual ~Integrator() = default;

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }
   void input(double in)
   {
      _out += 0.5 * (in + in_previous) * SimTime::delta_t;
      in_previous = in;
   }
   void reset() { _out = _initial_out; }

private:
   double in_previous = _initial_out;
};

// Forward Euler integration
class IntegratorEuler : public TimedSimBlockIO
{
public:
   IntegratorEuler(int id, double initial_out = 0)
      : TimedSimBlockIO{id, initial_out}
      , _initial_out{initial_out}
   {
   }
   virtual ~IntegratorEuler() = default;

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }
   void input(double in) { _out += in * SimTime::delta_t; }
   void reset() { _out = _initial_out; }

private:
   const double _initial_out;
};

// Trapezoidal integration
class IntegratorTrapezoidal : public TimedSimBlockIO
{
public:
   IntegratorTrapezoidal(int id, double initial_out = 0)
      : TimedSimBlockIO{id, initial_out}
      , _initial_out{initial_out}
      , _in_previous{0}
   {
   }
   virtual ~IntegratorTrapezoidal() = default;
   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }
   void input(double in)
   {
      _out += 0.5 * (in + _in_previous) * SimTime::delta_t;
      _in_previous = in;
   }
   void reset()
   {
      _out = _initial_out;
      _in_previous = 0.0;
   }

private:
   const double _initial_out;
   double _in_previous;
};

// @TBD not tested
class PI : public TimedSimBlockIO
{
public:
   PI(int id, double Kp, double tau_I, double initial_out = 0)
      : TimedSimBlockIO{id, initial_out}
      , _Kp{Kp}
      , _tau_I{tau_I}
      , _z{3, initial_out}
   {
   }
   virtual ~PI() = default;
   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }
   void input(double in)
   {
      _z.push_back(in);
      _z.pop_front();
      _out = _z[0] + _K1 * _z[1] + _K2 * _z[2];
   }
   void reset()
   {
      _z.clear();
      _z = {0, 0, 0};
   }

private:
   const double _Kp;
   const double _tau_I;
   const double _K1{_Kp * (1 + (1 / _tau_I))};
   const double _K2{_Kp};
   std::deque<double> _z;
};

// @TBD not tested
class PID : public TimedSimBlockIO
{
public:
   PID(int id, double Kp, double tau_I, double tau_D, double initValue = 0)
      : TimedSimBlockIO{id, initValue}
      , _Kp{Kp}
      , _tau_I{tau_I}
      , _tau_D{tau_D}
      , _z{4, initValue}
   {
   }
   virtual ~PID() = default;

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }
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

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      inputs_ = config.inputs;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }

   void input(double in) { out_ = (sample_++ % nSamples_ == 0) ? in : out_; }

private:
   const int nSamples_;
   int sample_;
};

} // namespace dysysim

#endif // DYSYSIM_H
