#ifndef FUZZYSET_H
#define FUZZYSET_H

#include <iosfwd>
#include <string>
#include <cmath>

inline bool compare(double d1, double d2, const double EPS = 0.01) 
{
   return std::fabs(d1 - d2) < EPS;
}

class OutputFuzzySet;

/// Base class for all fuzzy set classes.
class FuzzySet
{
   friend std::ostream &operator<<(std::ostream &os, const FuzzySet &fs);
   friend OutputFuzzySet operator||(const FuzzySet &lhs, const FuzzySet &rhs);
   friend OutputFuzzySet operator&&(const FuzzySet &lhs, const FuzzySet &rhs);
   friend OutputFuzzySet operator!(const FuzzySet &fs);

public:
   FuzzySet() = default;
   FuzzySet(const std::string &name)
      : name_{name}
      , mbs_{0.0}
   {
   }
   virtual ~FuzzySet() = default;

   double getMbs() const { return mbs_; }
   void clearMbs() const { mbs_ = 0.0; }

protected:
   std::string name_{"NOT_DEFINED"};
   mutable double mbs_{0.0};
   virtual std::ostream &write(std::ostream &os) const = 0;
};

#endif // FUZZYSET_H
