#ifndef OUTPUTFUZZYSETTRAPEZOIDAL_H
#define OUTPUTFUZZYSETTRAPEZOIDAL_H

#include "OutputFuzzySet.h"

#include <array>

///
/// \pre t0 < t1 < t2 < t3
class OutputFuzzySetTrapezoidal : public OutputFuzzySet
{
public:
   OutputFuzzySetTrapezoidal(const std::string &name, double t0, double t1,
                             double t2, double t3);
   ~OutputFuzzySetTrapezoidal() override = default;

   OutputFuzzySetTrapezoidal &operator=(const OutputFuzzySet &other);
   bool isRight() const { return compare(_t[2], _t[3]); }
   bool isLeft() const { return compare(_t[0], _t[1]); }
   std::pair<double, double> range() const override { return {_t[0], _t[3]}; }
   bool isSymmetrical() const override
   {
      return (compare(_t[0] - _t[1], _t[3] - _t[2]));
   }

   double firstOfMaxima() const override;
   double lastOfMaxima() const override;
   double meanOfMaximum() const override;
   double area() const override;

protected:
   std::array<double, 4> _t;

   std::ostream &write(std::ostream &os) const override;
};

#endif // OUTPUTFUZZYSETTRAPEZOIDAL_H
