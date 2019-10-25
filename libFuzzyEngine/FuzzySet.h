#ifndef FUZZYSET_H
#define FUZZYSET_H

#include "FuzzyLogic.h"

#include <cmath>
#include <iosfwd>
#include <string>

inline bool compare(double d1, double d2, const double EPS = 0.01)
{
   return std::fabs(d1 - d2) < EPS;
}

class OutputFuzzySet;

/// Base class for all fuzzy set classes.
class FuzzySet
{
   friend std::ostream &operator<<(std::ostream &os, const FuzzySet &fs);

   friend OutputFuzzySet lukasiewicz::operator||(const FuzzySet &lhs,
                                                 const FuzzySet &rhs);
   friend OutputFuzzySet lukasiewicz::operator&&(const FuzzySet &lhs,
                                                 const FuzzySet &rhs);
   friend OutputFuzzySet lukasiewicz::operator!(const FuzzySet &fs);

   friend OutputFuzzySet zadeh::operator||(const FuzzySet &lhs,
                                           const FuzzySet &rhs);
   friend OutputFuzzySet zadeh::operator&&(const FuzzySet &lhs,
                                           const FuzzySet &rhs);
   friend OutputFuzzySet zadeh::operator!(const FuzzySet &fs);

   friend OutputFuzzySet operator*(const OutputFuzzySet &lhs, double rhs);

public:
   FuzzySet() = default;
   FuzzySet(const std::string &name)
      : name_{name}
      , mbs_{0.0}
   {
   }
   virtual ~FuzzySet() = default;

   virtual double membership() const = 0;

   double getMbs() const { return mbs_; }
   void clearMbs() const { mbs_ = 0.0; }

protected:
   std::string name_{"NOT_DEFINED"};
   mutable double mbs_{0.0};
   virtual std::ostream &write(std::ostream &os) const = 0;
};

#endif // FUZZYSET_H
