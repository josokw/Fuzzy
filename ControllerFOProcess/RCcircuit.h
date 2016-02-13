#ifndef RCCIRCUIT
#define RCCIRCUIT

#include "DySySim.h"

class RCcircuit {
public:
   RCcircuit(double Tsample, double initValue, double RC):
      _INT{initValue}, _doSample{false}, _RC{RC} {}
   ~RCcircuit() = default;
   void input(double in) { _INT.input((in - _INT.output()) / _RC);
                           _out = _INT.output(); }
   double output() const { return _out; }
private:
   dysysim::Integrator _INT;
   bool _doSample;
   double _RC;
   double _out;
};

#endif // RCCIRCUIT

