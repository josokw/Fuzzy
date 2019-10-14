#ifndef INPUTFUZZYSET_H
#define INPUTFUZZYSET_H

#include "FuzzySet.h"

class InputFuzzySet : public FuzzySet
{
   friend OutputFuzzySet operator*(const InputFuzzySet &lhs, double rhs);

public:
   InputFuzzySet() = default;
   InputFuzzySet(const std::string &name)
      : FuzzySet{name}
   {
   }
   virtual ~InputFuzzySet() override = default;

   void setInput(double input)
   {
      input_ = input;
      mbs_ = membership();
   }

protected:
   double input_{0.0};

   std::ostream &write(std::ostream &os) const override;
   virtual double membership() const = 0;
};

#endif // INPUTFUZZYSET_H
