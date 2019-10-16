#ifndef OUTPUTFUZZYSET_H
#define OUTPUTFUZZYSET_H

#include "FuzzySet.h"

#include <iostream>
#include <string>

class OutputFuzzySet;

class OutputFuzzySet : public FuzzySet
{
   friend OutputFuzzySet operator*(const OutputFuzzySet &lhs, double rhs);

public:
   OutputFuzzySet() = default;
   OutputFuzzySet(const std::string &name)
      : FuzzySet{name}
   {
   }
   OutputFuzzySet(const FuzzySet &fs) { setMbs(fs.getMbs()); }

   void setMbs(double mbs) { mbs_ = (mbs > mbs_) ? mbs : mbs_; }
   virtual double meanOfMaximum() const { return 0; }
   virtual double firstOfMaxima() const { return 0; }
   virtual double lastOfMaxima() const { return 0; }

protected:
   std::ostream &write(std::ostream &os) const override;
};

#endif // OUTPUTFUZZYSET_H
