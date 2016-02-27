#ifndef DYSYSIM_H
#define DYSYSIM_H

#include "SimBlock.h"
#include "SimBlockO.h"
#include "SimBlockIO.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <functional>
#include <iostream>
#include <queue>

// Dynamical Systems Simulator: DySySim ========================================

namespace dysysim {

// Output blocks ---------------------------------------------------------------

class Constant: public SimBlockO {
public:
   Constant(int id, double constant):
      SimBlockO{id} { _out = constant; }
   virtual ~Constant() = default;
};

// Input output blocks ---------------------------------------------------------

class AlgebraicDelay: public SimBlockIO {
public:
   AlgebraicDelay(int id, double initValue):
      SimBlockIO{id}, _out_previous{initValue} {}
   virtual ~AlgebraicDelay() = default;
   void input(double in) {
      _out = _out_previous;
      _out_previous = in;
   }
private:
   double _out_previous;
};

class Attenuator: public SimBlockIO {
public:
   Attenuator(int id, double attenuation):
      SimBlockIO{id}, _attenuation{attenuation} {}
   virtual ~Attenuator() = default;
   void input(double in) {
      _out = in / _attenuation;
   }
private:
   const double _attenuation;
};

class Cos: public SimBlockIO {
public:
   Cos(int id, double multiplier = 1.0, double phase = 0.0):
      SimBlockIO{id}, _multipier{multiplier}, _phase{phase} {}
   virtual ~Cos() = default;
   void input(double in) {
      _out = std::cos(in * _multipier + _phase);
   }
private:
   const double _multipier;
   const double _phase;
};

class Divider: public SimBlockIO {
public:
   Divider(int id):
      SimBlockIO{id} {}
   virtual ~Divider() = default;
   void input(double in1, double in2) {
      _out = in1 / in2;
   }
};

class Gain: public SimBlockIO {
public:
   Gain(int id, double gain):
      SimBlockIO{id}, _gain(gain) {}
   virtual ~Gain() = default;
   void input(double in) {
      _out = in * _gain;
   }
private:
   const double _gain;
};

class Limit: public SimBlockIO {
public:
   Limit(int id, double min, double max):
      SimBlockIO{id}, _min(min), _max(max) {}
   virtual ~Limit() = default;
   void input(double in) {
      _out = std::min(std::max(_min, in), _max);
   }
private:
   const double _min;
   const double _max;
};

class Max: public SimBlockIO {
public:
   Max(int id):
      SimBlockIO{id} {}
   virtual ~Max() = default;
   void input(double in1, double in2) {
      _out = in1 > in2 ? in1 : in2;
   }
};

class Min: public SimBlockIO {
public:
   Min(int id):
      SimBlockIO{id} {}
   virtual ~Min() = default;
   void input(double in1, double in2) {
      _out = in1 < in2 ? in1 : in2;
   }
};

class Multiplier: public SimBlockIO {
public:
   Multiplier(int id):
      SimBlockIO{id} {}
   virtual ~Multiplier() = default;
   void input(double in1, double in2) {
      _out = in1 * in2;
   }
};

class Sin: public SimBlockIO {
public:
   Sin(int id, double multiplier = 1.0, double phase = 0.0):
      SimBlockIO{id}, _multiplier{multiplier}, _phase{phase} {}
   virtual ~Sin() = default;
   void input(double in) {
      _out = std::sin(in * _multiplier + _phase);
   }
private:
   const double _multiplier;
   const double _phase;
};

class Summator: public SimBlockIO {
public:
   Summator(int id):
      SimBlockIO{id} {}
   virtual ~Summator() = default;
   void input(double in1, double in2) {
      _out = in1 + in2;
   }
   void input(double in1, double in2, double in3) {
      _out = in1 + in2 + in3;
   }
   void input(double in1, double in2, double in3, double in4) {
      _out = in1 + in2 + in3 + in4;
   }
};

// Timed output blocks ---------------------------------------------------------

// Sinus generator, amplitude = 1
class Frequency: public TimedSimBlockO {
public:
   Frequency(int id, double frequency, double phase = 0.0):
      TimedSimBlockO{id}, _frequency{frequency}, _phase{phase} {}
   virtual ~Frequency() = default;
   void next() {
      _out = std::sin(2 * M_PI * _frequency * tc.t + _phase);
   }
private:
   const double _frequency;
   const double _phase;
};

class Step: public TimedSimBlockO {
public:
   Step(int id, double initialValue, double stepValue, double stepTime):
      TimedSimBlockO{id},
      _initialValue{initialValue}, _stepValue{stepValue},_stepTime{stepTime} {}
   virtual ~Step() = default;
   void next() {
      _out = (tc.t >= _stepTime) ? _stepValue : _initialValue;
   }
private:
   const double _initialValue;
   const double _stepValue;
   const double _stepTime;
};

class Time: public TimedSimBlockO {
public:
   Time(int id, double delta_t):
      TimedSimBlockO{id} {
      SimTime::delta_t = delta_t;
   }
   virtual ~Time() = default;
   void next() {
      Time::tc.next();
      _out = SimTime::t;
   }
};

// Timed input output blocks ---------------------------------------------------

class Delay: public TimedSimBlockIO {
public:
    Delay(int id, double delaytime, double initValue):
       TimedSimBlockIO{id, initValue}, _delaytime{delaytime}, _buffer{} {
       for (int i = 0; i < int(delaytime / tc.delta_t); i++) {
          _buffer.push(initValue);
       }
    }
    virtual ~Delay() = default;
    void input(double in) {
       _buffer.push(in);
       _out = _buffer.front();
       _buffer.pop();
    }
private:
    const double _delaytime;
    std::queue<double> _buffer;
};

class FirstOrder: public TimedSimBlockIO {
public:
   FirstOrder(int id, double timeConstant, double initValue = 0.0):
      TimedSimBlockIO{id, initValue}, _timeConstant{timeConstant} {}
   ~FirstOrder() = default;
   void input(double in) {
      _out += tc.delta_t * (in - _out) / _timeConstant;
   }
private:
   const double _timeConstant;
};

template<typename T>
class Function: public SimBlockIO {
public:
   Function(int id, std::function<double(T)>callback):
      SimBlockIO{id}, _callback{callback} {}
   virtual ~Function() = default;
   void input(double in) {
      _out = _callback(in);
   }
private:
   std::function<double(T)> _callback;
};

class OnOff: public SimBlockIO {
public:
   OnOff(int id, double onoff, double on, double off):
      SimBlockIO{id}, _onoff{onoff},_on(on), _off{off} {}
   virtual ~OnOff() = default;
   void input(double in) {
      _out = (in < _onoff) ? _off : _on;
   }
private:
   const double _onoff;
   const double _on;
   const double _off;
};

// Euler integration
class Integrator: public TimedSimBlockIO {
public:
   Integrator(int id, double initValue = 0):
      TimedSimBlockIO{id, initValue}, _initValue{initValue} {}
   virtual ~Integrator() = default;
   void input(double in) {
      _out += in * tc.delta_t;
   }
   void reset() {
      _out = _initValue;
   }
private:
   const double _initValue;
};

// Euler integration
class IntegratorEuler: public TimedSimBlockIO {
public:
   IntegratorEuler(int id, double initValue = 0):
      TimedSimBlockIO{id, initValue}, _initValue{initValue} {}
   virtual ~IntegratorEuler() = default;
   void input(double in) {
      _out += in * tc.delta_t;
   }
   void reset() {
      _out = _initValue;
   }
private:
   const double _initValue;
};

// @TBD not tested
class PI: public TimedSimBlockIO {
public:
   PI(int id, double Kp, double tau_I, double initValue = 0):
      TimedSimBlockIO{id, initValue},
      _Kp{Kp}, _tau_I{tau_I},
      _z{3, initValue} {}
   virtual ~PI() = default;
   void input(double in) {
      _z.push_back(in);
      _z.pop_front();
      _out = _z[0] + _K1 * _z[1] + _K2 * _z[2];
   }
   void reset() {
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
class PID: public TimedSimBlockIO {
public:
   PID(int id, double Kp, double tau_I, double tau_D, double initValue = 0):
      TimedSimBlockIO{id, initValue},
      _Kp{Kp}, _tau_I{tau_I}, _tau_D{tau_D},
      _z{4, initValue} {}
   virtual ~PID() = default;
   void input(double in) {
      _z.push_back(in);
      _z.pop_front();
      _out = _z[0] + _K1 * _z[1] + _K2 * _z[2] + _K3 * _z[3];
   }
   void reset() {
      _z.clear();
      _z = {0,0,0,0};
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

class ZeroOrderHold: public TimedSimBlockIO {
public:
   ZeroOrderHold(int id, int nSamples = 1):
      TimedSimBlockIO{id}, _nSamples{nSamples}, _sample{0} {}
   virtual ~ZeroOrderHold() = default;
   void input(double in) {
      _out = (_sample++ % _nSamples == 0) ? in : _out;
   }
private:
   const int _nSamples;
   int _sample;
};

}

#endif // DYSYSIM_H
