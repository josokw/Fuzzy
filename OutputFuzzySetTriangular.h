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
  std::array<double, 3> _t;
protected:
  virtual void write(std::ostream& os) const override;
};

#endif // OUTPUTFUZZYSETTRIANGULAR_H
