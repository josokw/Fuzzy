#include "InputFuzzySetTriangular.h"
#include <iostream>

InputFuzzySetTriangular::InputFuzzySetTriangular(const std::string& name,
                                                 double t1, double t2, double t3)
  : InputFuzzySet{name}
  , _t{t1, t2, t3}
{}

void InputFuzzySetTriangular::write(std::ostream &os) const {
  os << _name << " input = " << _input << " mbs = " << _mbs;
}

double InputFuzzySetTriangular::membership() const {
  _mbs = 0;
  if(_input > _t[0] && _input <= _t[1]) {
      _mbs = (_t[1] - _input) / (_t[1] - _t[0]);
    }
  else
    {
      if(_input > _t[1] && _input <= _t[2]) {
          _mbs = (_input - _t[2]) / (_t[1] - _t[2]);
        }
    }
  return _mbs;
}
