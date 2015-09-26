#ifndef INPUTFUZZYSETTRIANGULAR_H
#define INPUTFUZZYSETTRIANGULAR_H

#include "InputFuzzySet.h"
#include <array>

class InputFuzzySetTriangular : public InputFuzzySet
{
public:
  InputFuzzySetTriangular(const std::string& name,
                          double t0, double t1, double t2);
  virtual ~InputFuzzySetTriangular() = default;
protected:
  std::array<double, 3> _t;
  virtual double membership() const override;
};

#endif // INPUTFUZZYSETTRIANGULAR_H
