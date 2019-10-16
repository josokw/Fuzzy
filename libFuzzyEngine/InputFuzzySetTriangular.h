#ifndef INPUTFUZZYSETTRIANGULAR_H
#define INPUTFUZZYSETTRIANGULAR_H

#include "InputFuzzySet.h"

#include <array>

/// Triangular fuzzy set.
/// \pre t0 <= t1 < t2 OR t0 < t1 <= t2
class InputFuzzySetTriangular : public InputFuzzySet
{
public:
   InputFuzzySetTriangular(const std::string &name, double t0, double t1,
                           double t2);
   ~InputFuzzySetTriangular() override = default;

   bool isRight() const { return compare(_t[1], _t[2]); }
   bool isLeft() const { return compare(_t[0], _t[1]); }

protected:
   std::array<double, 3> _t;

   std::ostream &write(std::ostream &os) const override;
   double membership() const override;
};

#endif // INPUTFUZZYSETTRIANGULAR_H
