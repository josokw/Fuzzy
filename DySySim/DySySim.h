#ifndef DYSYSIM_H
#define DYSYSIM_H

#include "SimBlock.h"
#include <cmath>

// Dynamical Systems Simulator

namespace dysysim {

class Time: public TimedSimBlock {
public:
   Time(double TsimStep): TimedSimBlock{} { CommonTime::TsimStep = TsimStep; }
   void next() { Time::tc.next(); }
   double output() const override { return Time::tc.t; }
};

class Step: public TimedSimBlock {
public:
   Step(double initialValue, double stepValue, double stepTime):
      TimedSimBlock{},
      _initialValue{initialValue}, _stepValue{stepValue},_stepTime{stepTime} {}
   double output() const override { return tc.t >= _stepTime
                                    ? _stepValue : _initialValue; }
private:
   const double _initialValue;
   const double _stepValue;
   const double _stepTime;
};

//class FirstOrderHold: public TimedSimBlock {
//public:
//   FirstOrderHold(double Tsample): TimedSimBlock{}, _sampleTime{0} {}
//   void input(double in) { _out = doSample() ? in : _out; }
//   double output() const override { return _out; }
//private:
//   bool compareTimes() { return std::fabs(_sampleTime - Time::tc.t) < 0.01 * _sampleTime; }
//   bool doSample() const { return compareTimes(); }
//   double _sampleTime;
//   double _out;
//};

// Euler integration
class Integrator: public TimedSimBlock {
public:
   Integrator(double initValue):
      TimedSimBlock{}, _initValue{initValue}, _out{initValue} {}
   ~Integrator() = default;
   void input(double in) { _out += in * tc.TsimStep; }
   double output() const { return _out; }
   void reset() { _out = _initValue; }
private:
   double _initValue;
   double _out;
};

}

#endif // DYSYSIM_H
