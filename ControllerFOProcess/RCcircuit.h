#ifndef RCCIRCUIT
#define RCCIRCUIT

#include "DySySim.h"

class RCcircuit {
public:
   RCcircuit(int id, double RC, double initValue = 0.0):
      _RC{RC}, _INT{id, initValue}, _out{_INT.output()} {}
   ~RCcircuit() = default;
   void input(double in) { _INT.input((in - _INT.output()) / _RC);
                           _out = _INT.output(); }
   double output() const { return _out; }
private:
   const double _RC;
   dysysim::Integrator _INT;
   double _out;
};

#endif // RCCIRCUIT
