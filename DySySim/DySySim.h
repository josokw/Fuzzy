#ifndef DYSYSIM_H
#define DYSYSIM_H

#include "SimBlock.h"
#include <cmath>

// Dynamical Systems Simulator

namespace dysysim {

class Gain: public SimBlock {
public:
   Gain(int id, double gain): SimBlock{id}, _gain(gain) {}
   virtual ~Gain() = default;
   void input(double in) { _out = in * _gain; }
private:
   double _gain;
};

class Attenuator: public SimBlock {
public:
   Attenuator(int id, double att): SimBlock{id}, _att{att} {}
   virtual ~Attenuator() = default;
   void input(double in) { _out = in / _att; }
private:
   double _att;
};

class Summator: public SimBlock {
public:
   Summator(int id): SimBlock{id} {}
   virtual ~Summator() = default;
   void input(double in1, double in2) { _out = in1 + in2; }
   void input(double in1, double in2, double in3) { _out = in1 + in2 + in3; }
   void input(double in1, double in2, double in3, double in4)
      { _out = in1 + in2 + in3 + in4; }
};

class Time: public TimedSimBlock {
public:
   Time(int id, double TsimStep): TimedSimBlock{id} { CommonTime::TsimStep = TsimStep; }
   virtual ~Time() = default;
   // void input(double in) {Time::tc.next(); _out = CommonTime::t;} dummy
   void next() { Time::tc.next(); _out = CommonTime::t; }
};

class Step: public TimedSimBlock {
public:
   Step(int id, double initialValue, double stepValue, double stepTime):
      TimedSimBlock{id},
      _initialValue{initialValue}, _stepValue{stepValue},_stepTime{stepTime} {}
   virtual ~Step() = default;
   double output() const { return tc.t >= _stepTime ? _stepValue : _initialValue; }
private:
   const double _initialValue;
   const double _stepValue;
   const double _stepTime;
};

class ZeroOrderHold: public TimedSimBlock {
public:
   ZeroOrderHold(int id, int nSamples = 1):
      TimedSimBlock{id}, _nSamples{nSamples}, _sample{0} {}
   virtual ~ZeroOrderHold() = default;
   void input(double in) { _out = (_sample++ % _nSamples == 0) ? in : _out; }
private:
   const int _nSamples;
   int _sample;
};

// Euler integration
class Integrator: public TimedSimBlock {
public:
   Integrator(int id, double initValue = 0):
      TimedSimBlock{id, initValue}, _initValue{initValue} {}
   virtual ~Integrator() = default;
   void input(double in) { _out += in * tc.TsimStep; }
   void reset() { _out = _initValue; }
private:
   double _initValue;
};

}

#endif // DYSYSIM_H