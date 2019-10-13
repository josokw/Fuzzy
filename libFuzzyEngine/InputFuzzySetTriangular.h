#ifndef INPUTFUZZYSETTRIANGULAR_H
#define INPUTFUZZYSETTRIANGULAR_H

#include "InputFuzzySet.h"

#include <array>

/// Triangular fuzzy set.
/// \pre t0 < t1 < t2
class InputFuzzySetTriangular : public InputFuzzySet
{
public:
   InputFuzzySetTriangular(const std::string &name, double t0, double t1,
                           double t2);
   ~InputFuzzySetTriangular() override = default;

protected:
   std::array<double, 3> _t;

   double membership() const override;
};

#endif // INPUTFUZZYSETTRIANGULAR_H
