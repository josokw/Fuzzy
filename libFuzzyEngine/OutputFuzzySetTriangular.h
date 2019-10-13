#ifndef OUTPUTFUZZYSETTRIANGULAR_H
#define OUTPUTFUZZYSETTRIANGULAR_H

#include "OutputFuzzySet.h"

#include <array>

class OutputFuzzySetTriangular : public OutputFuzzySet
{
public:
   OutputFuzzySetTriangular(const std::string &name, double t0, double t1,
                            double t2);
   ~OutputFuzzySetTriangular() override = default;

   OutputFuzzySetTriangular &operator=(const OutputFuzzySet &other);
   double firstOfMaxima() const override;
   double lastOfMaxima() const override;
   double meanOfMaximum() const override;

protected:
   std::array<double, 3> _t;
};

#endif // OUTPUTFUZZYSETTRIANGULAR_H
