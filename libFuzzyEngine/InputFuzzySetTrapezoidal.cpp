#include "InputFuzzySetTrapezoidal.h"
#include <iostream>

InputFuzzySetTrapezoidal::InputFuzzySetTrapezoidal(const std::string &name,
                                                   double t0, double t1,
                                                   double t2, double t3)
   : InputFuzzySet{name}
   , _t{t0, t1, t2, t3}
{
}

double InputFuzzySetTrapezoidal::membership() const
{
   double min1, min2, min3;

   // Left trapezoidal fuzzy set
   if (isLeft()) {
      min1 = 1.0;
      min2 = std::min((_t[3] - input_) / (_t[3] - _t[2]), 1.0);
      min3 = std::min(min1, min2);
   } else {
      // Right trapezoidal fuzzy set
      if (isRight()) {
         min1 = std::min((input_ - _t[0]) / (_t[1] - _t[0]), 1.0);
         min2 = 1.0;
         min3 = std::min(min1, min2);
      } else {
         min1 = std::min((input_ - _t[0]) / (_t[1] - _t[0]), 1.0);
         min2 = std::min((_t[3] - input_) / (_t[3] - _t[2]), 1.0);
         min3 = std::min(min1, min2);
      }
   }
   mbs_ = std::max(min3, 0.0);

   return mbs_;
}

std::ostream &InputFuzzySetTrapezoidal::write(std::ostream &os) const
{
   return InputFuzzySet::write(os)
          << " (" << _t[0] << ", " << _t[1] << ", " << _t[2] << ", " << _t[3]
          << ")  input = " << input_ << "  mbs = " << mbs_;
}
