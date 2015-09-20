#ifndef INPUTFUZZYSETTRAPEZOIDAL_H
#define INPUTFUZZYSETTRAPEZOIDAL_H


#include "InputFuzzySet.h"
#include <array>

class InputFuzzySetTrapezoidal : public InputFuzzySet
{
public:
  InputFuzzySetTrapezoidal(const std::string& name,
                          double t0, double t1, double t2, double t4);
  virtual ~InputFuzzySetTrapezoidal() = default;
protected:
  std::array<double, 4> _t;
  virtual double membership() const override;
};

#endif // INPUTFUZZYSETTRAPEZOIDAL_H
