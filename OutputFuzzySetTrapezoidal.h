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
  std::array<double, 4> _t;
protected:

};

#endif // OUTPUTFUZZYSETTRAPEZOIDAL_H
