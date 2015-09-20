#ifndef OUTPUTFUZZYSET_H
#define OUTPUTFUZZYSET_H

#include "FuzzySet.h"
#include <string>

class OutputFuzzySet : public FuzzySet
{
public:
  OutputFuzzySet() = default;
  OutputFuzzySet(const std::string& name): FuzzySet{name} {}
  void setMbs(double mbs) const { _mbs = mbs; }
protected:
  virtual void write(std::ostream& os) const override;
};

#endif // OUTPUTFUZZYSET_H
