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
   double firstOfMaxima() const override;
   double lastOfMaxima() const override;
   double meanOfMaximum() const override;

protected:
   std::array<double, 4> _t;
};

#endif // OUTPUTFUZZYSETTRAPEZOIDAL_H
