#ifndef DYSYSIM_H
#define DYSYSIM_H

#include "SimBlock.h"
#include <cmath>

// Dynamical Systems Simulator

namespace dysysim {

class Time: public TimedSimBlock {
public:
   Time(double TsimStep): TimedSimBlock{} { CommonTime::TsimStep = TsimStep; }
   virtual ~Time() = default;
   void next() { Time::tc.next(); }
   double output() const override { return Time::tc.t; }
};

class Step: public TimedSimBlock {
public:
   Step(double initialValue, double stepValue, double stepTime):
      TimedSimBlock{},
      _initialValue{initialValue}, _stepValue{stepValue},_stepTime{stepTime} {}
   virtual ~Step() = default;
   double output() const override { return tc.t >= _stepTime
                                    ? _stepValue : _initialValue; }
private:
   const double _initialValue;
   const double _stepValue;
   const double _stepTime;
};

class ZeroOrderHold: public TimedSimBlock {
public:
   ZeroOrderHold(int nSamples = 1):
      TimedSimBlock{}, _nSamples{nSamples}, _sample{0} {}
   virtual ~ZeroOrderHold() = default;
   void input(double in) { _out = (_sample++ % _nSamples == 0) ? in : _out; }
   double output() const override { return _out; }
private:
   const int _nSamples;
   int _sample;
   double _out;
};

// Euler integration
class Integrator: public TimedSimBlock {
public:
   Integrator(double initValue):
      TimedSimBlock{}, _initValue{initValue}, _out{initValue} {}
   virtual ~Integrator() = default;
   void input(double in) { _out += in * tc.TsimStep; }
   double output() const { return _out; }
   void reset() { _out = _initValue; }
private:
   double _initValue;
   double _out;
};

}

#endif // DYSYSIM_H
