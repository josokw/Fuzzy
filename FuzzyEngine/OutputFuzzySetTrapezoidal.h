#ifndef OUTPUTFUZZYSETTRAPEZOIDAL_H
#define OUTPUTFUZZYSETTRAPEZOIDAL_H

#include "OutputFuzzySet.h"
#include <array>

class OutputFuzzySetTrapezoidal : public OutputFuzzySet
{
public:
  OutputFuzzySetTrapezoidal(const std::string& name,
                            double t0, double t1, double t2, double t3);
  virtual ~OutputFuzzySetTrapezoidal() = default;
  OutputFuzzySetTrapezoidal& operator=(const OutputFuzzySet& other);
  virtual double meanOfMaximum() const override { return (_t[1] + _t[2]) / 2; }
  virtual double firstOfMaxima() const override { return _t[1]; }
  virtual double lastOfMaxima() const override { return _t[2]; }
protected:
  std::array<double, 4> _t;
};

#endif // OUTPUTFUZZYSETTRAPEZOIDAL_H
