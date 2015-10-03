#ifndef INPUTFUZZYSET_H
#define INPUTFUZZYSET_H

#include "FuzzySet.h"

class InputFuzzySet : public FuzzySet
{
  friend OutputFuzzySet operator*(const InputFuzzySet& lhs, double rhs);
public:
  InputFuzzySet() = default;
  InputFuzzySet(const std::string& name): FuzzySet{name} {}
  virtual ~InputFuzzySet() = default;
  void setInput(double input) { _input = input; membership(); }
protected:
  double _input = 0;
  virtual std::ostream& write(std::ostream& os) const override;
  virtual double membership() const = 0;
};

#endif // INPUTFUZZYSET_H
