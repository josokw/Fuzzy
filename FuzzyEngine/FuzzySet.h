#ifndef FUZZYSET_H
#define FUZZYSET_H

#include <iosfwd>
#include <string>

class OutputFuzzySet;

class FuzzySet
{
   friend std::ostream &operator<<(std::ostream &os, const FuzzySet &fs);
   friend OutputFuzzySet operator||(const FuzzySet &lhs, const FuzzySet &rhs);
   friend OutputFuzzySet operator&&(const FuzzySet &lhs, const FuzzySet &rhs);
   friend OutputFuzzySet operator!(const FuzzySet &fs);

public:
   FuzzySet()
      : _name{}
      , _mbs{0}
   {
   }
   FuzzySet(const std::string &name)
      : _name{name}
      , _mbs{0}
   {
   }
   virtual ~FuzzySet() = default;

   double getMbs() const { return _mbs; }

protected:
   std::string _name = "";
   mutable double _mbs;
   virtual std::ostream &write(std::ostream &os) const = 0;
};

#endif // FUZZYSET_H
