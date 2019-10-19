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
   std::pair<double, double> range() const override { return {_t[0], _t[2]}; }
   bool isSymmetrical() const override
   {
      return (compare(_t[0] - _t[1], _t[2] - _t[1]));
   }

   double firstOfMaxima() const override;
   double lastOfMaxima() const override;
   double meanOfMaximum() const override;
   double area() const override;

protected:
   std::array<double, 3> _t;

   std::ostream &write(std::ostream &os) const override;
};

#endif // OUTPUTFUZZYSETTRIANGULAR_H
