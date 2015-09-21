#ifndef OUTPUTFUZZYSET_H
#define OUTPUTFUZZYSET_H

#include "FuzzySet.h"
#include <string>

class OutputFuzzySet : public FuzzySet
{
public:
  OutputFuzzySet(): FuzzySet{} {}
  OutputFuzzySet(const std::string& name): FuzzySet{name} {}
  OutputFuzzySet(const FuzzySet& fs) { _mbs = fs.getMbs(); }
  void setMbs(double mbs) { _mbs = mbs; }
  virtual double meanOfMaximum() const { return 0; }
protected:
  virtual void write(std::ostream& os) const override;
};

#endif // OUTPUTFUZZYSET_H
