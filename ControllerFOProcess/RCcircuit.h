#ifndef RCCIRCUIT
#define RCCIRCUIT

class Step {
public:
   Step(double stepTime): _stepTime{stepTime} {}
   double output(double t) const { return t > _stepTime ? 1 : 0; }
private:
   const double _stepTime;
};

class Integrator {
public:
   Integrator(double Ts, double initValue):
      _Ts{Ts}, _initValue{initValue}, _out{initValue} {}
   ~Integrator() = default;
   void input(double in) { _out += in * _Ts; }
   double output() const { return _out; }
   void reset() { _out = _initValue; }
private:
   double _Ts;
   double _initValue;
   double _out;
};

class RCcircuit {
public:
   RCcircuit(double Ts, double initValue, double RC):
      _INT{Ts, initValue}, _RC{RC} {}
   ~RCcircuit() = default;
   void input(double in) { _INT.input((in - _INT.output()) / _RC);
                           _out = _INT.output(); }
   double output() const { return _out; }
private:
   Integrator _INT;
   double _RC;
   double _out;
};

#endif // RCCIRCUIT

