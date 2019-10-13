#ifndef INPUTFUZZYSETTRAPEZOIDAL_H
#define INPUTFUZZYSETTRAPEZOIDAL_H

#include "InputFuzzySet.h"

#include <array>

/// Trapezoidal fuzzy set.
/// \pre t0 < t1 <= t2 < t3
class InputFuzzySetTrapezoidal : public InputFuzzySet
{
public:
   InputFuzzySetTrapezoidal(const std::string &name, double t0, double t1,
                            double t2, double t3);
   ~InputFuzzySetTrapezoidal() override = default;

protected:
   std::array<double, 4> _t;
   
   double membership() const override;
};

#endif // INPUTFUZZYSETTRAPEZOIDAL_H
