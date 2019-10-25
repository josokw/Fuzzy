#ifndef OUTPUTFUZZYSETSINGLETON_H
#define OUTPUTFUZZYSETSINGLETON_H

#include "OutputFuzzySet.h"

#include <array>

class OutputFuzzySetSingleton : public OutputFuzzySet
{
public:
   OutputFuzzySetSingleton(const std::string &name, double t0);
   ~OutputFuzzySetSingleton() override = default;

   OutputFuzzySetSingleton &operator=(const OutputFuzzySet &other);
   std::pair<double, double> range() const override { return {_t[0], _t[0]}; }
   bool isSymmetrical() const override { return true; }

   double firstOfMaxima() const override;
   double lastOfMaxima() const override;
   double meanOfMaximum() const override;
   double area() const override;

protected:
   std::array<double, 1> _t;

   std::ostream &write(std::ostream &os) const override;
};

#endif // OUTPUTFUZZYSETSINGLETON_H
