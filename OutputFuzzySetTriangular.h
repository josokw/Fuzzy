#ifndef OUTPUTFUZZYSETTRIANGULAR_H
#define OUTPUTFUZZYSETTRIANGULAR_H

#include "OutputFuzzySet.h"
#include <array>

class OutputFuzzySetTriangular : public OutputFuzzySet
{
public:
  OutputFuzzySetTriangular(const std::string& name,
                           double t0, double t1, double t2);
  virtual ~OutputFuzzySetTriangular() = default;
  virtual double meanOfMaximum() const override { return _t[1]; }
protected:
  std::array<double, 3> _t;
};

#endif // OUTPUTFUZZYSETTRIANGULAR_H
