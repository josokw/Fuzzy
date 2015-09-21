#include "InputFuzzySetTrapezoidal.h"
#include <iostream>

InputFuzzySetTrapezoidal::InputFuzzySetTrapezoidal(const std::string& name,
                                                   double t1, double t2,
                                                   double t3, double t4)
  : InputFuzzySet{name}
  , _t{t1, t2, t3, t4}
{}

double InputFuzzySetTrapezoidal::membership() const {
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
      _mbs = 1;
    }
  else if(_input <= _t[3])
    {
      if(_t[2] == _t[3])
        {
          _mbs = 1;
        }
      else
        {
          _mbs = 1 - ((_input - _t[2]) / (_t[3] - _t[2]));
        }
    }
  else
    {
      _mbs = 0;
    }

  return _mbs;
}
