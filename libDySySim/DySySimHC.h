#ifndef DYSYSIMHC_H
#define DYSYSIMHC_H

#include "SimBlockHC.h"

namespace dysysim {

/// Trapezoidal integration
class IntegratorHC : public SimBlockHC
{
public:
   IntegratorHC(dysysim::SimBlock &parent_simblock, int n_inputs);
   ~IntegratorHC() override = default;

   void exe() override { input(sumInputs()); }

   void input(double in)
   {
      out_ += 0.5 * (in + in_previous) * SimTime::delta_t;
      in_previous = in;
   }

private:
   double initial_out_{0.0};
   double in_previous{initial_out_};
};

} // namespace dysysim

#endif
