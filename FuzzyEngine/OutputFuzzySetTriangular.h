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
  OutputFuzzySetTriangular& operator=(const OutputFuzzySet& other);
  virtual double meanOfMaximum() const override { return _t[1]; }
  virtual double firstOfMaxima() const override { return _t[0]; }
  virtual double lastOfMaxima() const override { return _t[2]; }
protected:
  std::array<double, 3> _t;
};

#endif // OUTPUTFUZZYSETTRIANGULAR_H