#ifndef DYSYSIM_H
#define DYSYSIM_H

#include "SimBlock.h"
#include "SimBlockO.h"
#include "SimBlockIO.h"
#include <cmath>
#include <functional>
#include <iostream>
#include <queue>

// Dynamical Systems Simulator

namespace dysysim {

class Constant: public SimBlockO {
public:
   Constant(int id, double constant): SimBlockO{id} { _out = constant; }
   virtual ~Constant() = default;
};

class Gain: public SimBlockIO {
public:
   Gain(int id, double gain): SimBlockIO{id}, _gain(gain) {}
   virtual ~Gain() = default;
   void input(double in) {
      _out = in * _gain;
   }
private:
   double _gain;
};

class Attenuator: public SimBlockIO {
public:
   Attenuator(int id, double att): SimBlockIO{id}, _att{att} {}
   virtual ~Attenuator() = default;
   void input(double in) {
      _out = in / _att;
   }
private:
   double _att;
};

class Multiplier: public SimBlockIO {
public:
   Multiplier(int id): SimBlockIO{id} {}
   virtual ~Multiplier() = default;
   void input(double in1, double in2) {
      _out = in1 * in2;
   }
};

class Divider: public SimBlockIO {
public:
   Divider(int id): SimBlockIO{id} {}
   virtual ~Divider() = default;
   void input(double in1, double in2) {
      _out = in1 / in2;
   }
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

class Saturation: public SimBlockIO {
public:
   Saturation(int id, double min, double max):
      SimBlockIO{id}, _min(min), _max(max) {}
   virtual ~Saturation() = default;
   void input(double in) {
      _out = std::min(std::max(_min, in), _max);
   }
private:
   double _min;
   double _max;
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

class Time: public TimedSimBlockO {
public:
   Time(int id, double TsimStep):
      TimedSimBlockO{id} {
      SimTime::TsimStep = TsimStep;
   }
   virtual ~Time() = default;
   void next() {
      Time::tc.next();
      _out = SimTime::t;
   }
};

class Step: public TimedSimBlockO {
public:
   Step(int id, double initialValue, double stepValue, double stepTime):
      TimedSimBlockO{id},
      _initialValue{initialValue}, _stepValue{stepValue},_stepTime{stepTime} {}
   virtual ~Step() = default;
   void next() {
      _out = tc.t >= _stepTime ? _stepValue : _initialValue;
   }
private:
   const double _initialValue;
   const double _stepValue;
   const double _stepTime;
};

class ZeroOrderHold: public TimedSimBlockIO {
public:
   ZeroOrderHold(int id, int nSamples = 1):
      TimedSimBlockIO{id}, _nSamples{nSamples}, _sample{0} {}
   virtual ~ZeroOrderHold() = default;
   void input(double in) { _out = (_sample++ % _nSamples == 0) ? in : _out; }
private:
   const int _nSamples;
   int _sample;
};

class OnOff: public SimBlockIO {
public:
   OnOff(int id, double onoff, double on, double off):
      SimBlockIO{id}, _onoff{onoff},_on(on), _off{off} {}
   virtual ~OnOff() = default;
   void input(double in) { _out = in < _onoff ? _off : _on; }
private:
   double _onoff;
   double _on;
   double _off;
};

// Euler integration
class Integrator: public TimedSimBlockIO {
public:
   Integrator(int id, double initValue = 0):
      TimedSimBlockIO{id, initValue}, _initValue{initValue} {}
   virtual ~Integrator() = default;
   void input(double in) { _out += in * tc.TsimStep; }
   void reset() { _out = _initValue; }
private:
   double _initValue;
};

class FirstOrder: public TimedSimBlockIO {
public:
   FirstOrder(int id, double timeConstant, double initValue = 0.0):
      TimedSimBlockIO{id, initValue}, _timeConstant{timeConstant} {}
   ~FirstOrder() = default;
   void input(double in) {
      _out += tc.TsimStep * (in - _out) / _timeConstant;
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

class DeadTime: public TimedSimBlockO {
public:
    DeadTime(int id, double deadtime, double initValue):
       TimedSimBlockO{id, initValue}, _deadtime{deadtime}, _buffer{} {
       for (int i = 0; i < int(deadtime / tc.TsimStep); i++) {
          _buffer.push(initValue);
       }
    }
    virtual ~DeadTime() = default;
    void input(double in) {
       _buffer.push(in);
       _out = _buffer.front(); _buffer.pop();
    }
private:
    double _deadtime;
    std::queue<double> _buffer;
};

}

#endif // DYSYSIM_H
