#ifndef SIMBLOCK_H
#define SIMBLOCK_H

#include "ErrorCodes.h"

#include <cmath>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <system_error>
#include <vector>

namespace dysysim {

class SimContext;

// For logic related simblocks
inline constexpr double LOGIC01{0.5};
inline bool is_0(double in)
{
   return in < LOGIC01;
}
inline bool is_1(double in)
{
   return in >= LOGIC01;
}
inline double convert01(double in)
{
   if (is_0(in))
      return 0.0;
   return 1.0;
}

/// Abstract Base Class for all simulation block derived classes.
class SimBlock
{
public:
   using ioType_t = enum class ioType {
      input0,        ///< SimBlock has no inputs
      input1,        ///< SimBlock has 1 input
      input2,        ///< SimBlock has 2 inputs
      input3,        ///< SimBlock has 3 inputs
      input1N,       ///< SimBlock has >= 1 inputs
      input2N,       ///< SimBlock has >= 2 inputs
      input1Noutput0 ///< Simblock has no output only side effects
   };

   using configData_t = struct ConFigData {
      int id;
      std::vector<int> inputs;
      std::vector<double> parameters;
   };

   SimBlock(const std::string &blockType, const ioType_t ioType)
      : blockType_{blockType}
      , ioType_{ioType}
      , id_{-1}
      , inputs_{}
      , out_{0.0}
      , has_history_{false}
      , context_{nullptr}
   {
   }
   SimBlock(const SimBlock &other) = delete;
   SimBlock &operator=(const SimBlock &other) = delete;
   virtual ~SimBlock() = default;

   const std::string &getBlockType() const { return blockType_; }
   ioType_t getIOType() const { return ioType_; }
   int getId() const { return id_; }
   double sumInputs() const;
   double andInputs() const;
   double orInputs() const;
   double notInput() const;
   double output() const { return out_; }

   const std::vector<int> &getInputs() const { return inputs_; }
   bool hasHistory() const { return has_history_; }
   void setContext(SimContext *ctx) { context_ = ctx; }
   const SimContext *getContext() const { return context_; }

   virtual std::shared_ptr<SimBlock> create() = 0;
   /// Returns the expected number of parameters for this block.
   virtual size_t n_params(const configData_t & /*config*/) const { return 0; }
   /// Checks all config data, returns a vector of all errors.
   virtual std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const;
   virtual std::vector<std::error_code> config(const configData_t &config) = 0;
   /// Calculate out_ for t = t_n
   virtual void exe()
   {
      std::cerr << blockType_ << " --- exe() NOT implemented\n";
   }

protected:
   const std::string blockType_;
   const ioType_t ioType_;
   int id_;
   std::vector<int> inputs_;
   double out_;
   bool has_history_;
   SimContext *context_;

   std::error_code allInputsAvailable();
};

} // namespace dysysim

#endif // SIMBLOCK_H
