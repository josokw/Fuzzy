#ifndef SIMBLOCK_H
#define SIMBLOCK_H

#include "ErrorCodes.h"

#include <fstream>
#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <system_error>
#include <vector>

namespace dysysim {

// For logic related simblocks
const double LOGIC01{0.5};
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

/// SimTime contains simulation time data.
/// \todo Consider implementation as a struct?
/// \todo Consider implementation t as std::chrono::...
class SimTime
{
public:
   SimTime() = default;
   ~SimTime() = default;

   static double delta_t;
   static double end_t;
   static int width_t;
   static int precision_t;
   static double t;

   static void set(double delta, double end);
   static double output() { return t; }
   static void reset() { t = 0.0; }
   static void next() { t += delta_t; }
   static bool simulation_on();
};

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

   SimBlock(const std::string &blockType, const ioType_t ioType,
            size_t n_params = 0)
      : blockType_{blockType}
      , ioType_{ioType}
      , id_{-1}
      , inputs_{}
      , out_{0.0}
      , n_params_{n_params}
      , has_history_{false}
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

   virtual std::shared_ptr<SimBlock> create() = 0;
   /// Checks all config data, returns a vector of all errors.
   virtual std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const;
   virtual std::vector<std::error_code> config(const configData_t &config) = 0;
   /// Calculate out_ for t = t_n
   virtual void exe()
   {
      std::cerr << blockType_ << " --- exe() NOT implemented\n";
   }

   static void clearSimBlocks() { allSimBlocks_s.clear(); }
   static auto getSimBlock(int id) { return allSimBlocks_s.at(id); }
   static bool idIsUnique(int id);
   static std::error_code addSimBlock(int id, std::shared_ptr<SimBlock> pSB);
   static std::error_code setExeSequence();
   static void setExeSequence(std::vector<int> &exeSequence);
   /// Calculates all SimBlock out_ for t = 0.
   static void initSimBlocks();
   /// Calculates all SimBlock out_ for t = t_n (n > 0).
   static void exeSimBlocks();

public:
   static std::map<int, std::shared_ptr<SimBlock>> allSimBlocks_s;
   static SimTime sim_time;

protected:
   const std::string blockType_;
   const ioType_t ioType_;
   int id_;
   std::vector<int> inputs_;
   double out_;
   mutable size_t n_params_;
   bool has_history_;

   std::error_code allInputsAvailable();
   bool allInputsInExeSequence();
   bool IdInExeSequence(int id);

   static std::vector<int> exeSequence_s;
};

} // namespace dysysim

#endif // SIMBLOCK_H
