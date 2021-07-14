#ifndef INPUTFUZZYSET_H
#define INPUTFUZZYSET_H

#include "FuzzySet.h"

/// Abstract base class for input fuzzy sets.
class InputFuzzySet : public FuzzySet
{
   friend OutputFuzzySet operator*(const InputFuzzySet &lhs, double rhs);

public:
   InputFuzzySet() = default;
   InputFuzzySet(const std::string &name)
      : FuzzySet{name}
   {
   }
   ~InputFuzzySet() override = default;

   void setInput(double input)
   {
      input_ = input;
      mbs_ = membership();
   }


protected:
   double input_{0.0};

   std::ostream &write(std::ostream &os) const override;
   double membership() const override  { return 0.0; }
};

#endif // INPUTFUZZYSET_H
