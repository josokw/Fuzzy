#ifndef SIMBLOCKHC_H
#define SIMBLOCKHC_H

#include "ErrorCodes.h"
#include "SimBlock.h"

#include <fstream>
#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <system_error>
#include <vector>

namespace dysysim {

// // For logic related simblocks
// const double LOGIC01{0.5};
// inline bool is_0(double in)
// {
//    return in < LOGIC01;
// }
// inline bool is_1(double in)
// {
//    return in >= LOGIC01;
// }
// inline double convert01(double in)
// {
//    if (is_0(in))
//       return 0.0;
//    return 1.0;
// }

/// Abstract Base Class for all hard coded simulation block derived classes.
/// Uses a SimBlock object reposible for managing inputs, output and parameters.
class SimBlockHC
{
   friend dysysim::SimBlockHC &operator>>(double lhs, dysysim::SimBlockHC &rhs);
   friend dysysim::SimBlockHC &operator>>(dysysim::SimBlockHC &lhs,
                                          dysysim::SimBlockHC &rhs);

public:
   // using ioType_t = enum class ioType {
   //    input0,        ///< SimBlock has no inputs
   //    input1,        ///< SimBlock has 1 input
   //    input2,        ///< SimBlock has 2 inputs
   //    input3,        ///< SimBlock has 3 inputs
   //    input1N,       ///< SimBlock has >= 1 inputs
   //    input2N,       ///< SimBlock has >= 2 inputs
   //    input1Noutput0 ///< Simblock has no output only side effects
   // };

   // using configData_t = struct ConFigData {
   //    int id;
   //    std::vector<int> inputs;
   //    std::vector<double> parameters;
   // };

   SimBlockHC(SimBlock &simblock, int n_inputs)
      : simblock_{simblock}
      , n_inputs_(n_inputs)
      , inputs_(n_inputs, 0.0)
   {
   }
   SimBlockHC(const SimBlockHC &other) = delete;
   SimBlockHC &operator=(const SimBlockHC &other) = delete;
   virtual ~SimBlockHC() = default;

    double &operator [] (int index) {
        return inputs_[index];
    }

   double sumInputs() const;
   double andInputs() const;
   double orInputs() const;
   double notInput() const;
   double output() const { return out_; }

   virtual void exe() = 0;

public:
   static SimTime sim_time;

protected:
   SimBlock &simblock_;
   size_t n_inputs_;
   std::vector<double> inputs_;
   double out_;
};

} // namespace dysysim

#endif // SIMBLOCKHC_H
