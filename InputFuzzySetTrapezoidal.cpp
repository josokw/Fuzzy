#include "InputFuzzySetTrapezoidal.h"

#include "InputFuzzySetTrapezoidal.h"
#include <iostream>

InputFuzzySetTrapezoidal::InputFuzzySetTrapezoidal(const std::string& name,
                                                   double t1, double t2,
                                                   double t3, double t4)
  : InputFuzzySet{name}
  , _t{t1, t2, t3, t4}
{}

double InputFuzzySetTrapezoidal::membership() const {
  _mbs = 0;
  if(_input > _t[0] && _input <= _t[1]) {
      _mbs = (_t[1] - _input) / (_t[1] - _t[0]);
    }
  else
    {
      if(_input > _t[2] && _input <= _t[3]) {
          _mbs = (_input - _t[3]) / (_t[2] - _t[3]);
        }
      else
        {
          if(_input > _t[1] && _input < _t[2] ) {
              _mbs = 1;
            }
        }
    }
  return _mbs;
}
