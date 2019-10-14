#ifndef INPUTFUZZYSETTRAPEZOIDAL_H
#define INPUTFUZZYSETTRAPEZOIDAL_H

#include "InputFuzzySet.h"

#include <array>

/// Trapezoidal fuzzy set.
/// \pre t0 <= t1 < t2 < t3 OR t0 < t1 < t2 <= t3
class InputFuzzySetTrapezoidal : public InputFuzzySet
{
public:
   InputFuzzySetTrapezoidal(const std::string &name, double t0, double t1,
                            double t2, double t3);
   ~InputFuzzySetTrapezoidal() override = default;

   bool isRight() const { return compare(_t[2], _t[3]); }
   bool isLeft() const { return compare(_t[0], _t[1]); }

protected:
   std::array<double, 4> _t;

   double membership() const override;
};

#endif // INPUTFUZZYSETTRAPEZOIDAL_H
