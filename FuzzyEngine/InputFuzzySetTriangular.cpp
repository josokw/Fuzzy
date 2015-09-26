#include "InputFuzzySetTriangular.h"
#include <iostream>

InputFuzzySetTriangular::InputFuzzySetTriangular(const std::string& name,
                                                 double t0, double t1, double t2)
  : InputFuzzySet{name}
  , _t{t0, t1, t2}
{}

double InputFuzzySetTriangular::membership() const {
  if(_input < _t[0])
    {
      _mbs = 0;
    }
  else if(_input <= _t[1])
    {
      if(_t[0] == _t[1])
        {
          _mbs = 1;
        }
      else
        {
          _mbs = (_input - _t[0]) / (_t[1] - _t[0]);
        }
    }
  else if(_input <= _t[2])
    {
      if(_t[1] == _t[2])
        {
          _mbs = 1;
        }
      else
        {
          _mbs = 1 - ((_input - _t[1]) / (_t[2] - _t[1]));
        }
    }
  else
    {
      _mbs = 0;
    }

  return _mbs;
}
