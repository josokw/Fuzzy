#ifndef SIMBLOCK_H
#define SIMBLOCK_H

#include <fstream>
#include <initializer_list>
#include <iostream>
#include <map>
#include <vector>

namespace dysysim {

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
      input0,      ///< SimBlock has no inputs
      history,     ///< Simblock has state (history)
      inputoutput, ///< Simblock has in- and output, no state
      output0      ///< Simblock has no output only side effects
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
   {
   }
   SimBlock(const SimBlock &other) = delete;
   SimBlock &operator=(const SimBlock &other) = delete;
   virtual ~SimBlock() = default;

   const std::string &getBlockType() const { return blockType_; }
   ioType_t getIOType() const { return ioType_; }
   int getId() const { return id_; }
   double output() const { return out_; }

   virtual SimBlock *create() = 0;
   virtual void config(const configData_t &config) = 0;
   /// Calculate out_ for t = t_n
   virtual void exe()
   {
      std::cerr << blockType_ << " --- exe() NOT implemented\n";
   }

   static void clearSimBlocks() { allSimBlocks_s.clear(); }
   static SimBlock *getSimBlock(int id) { return allSimBlocks_s.at(id); }
   static void addSimBlock(int id, SimBlock* pSB) { allSimBlocks_s[id] = pSB; }
   static bool idIsUnique(int id);
   static void setExeSequence();
   static void setExeSequence(std::vector<int> &exeSequence);
   /// Calculate all SimBlock out_ for t = 0.
   static void initSimBlocks();
   /// Calculate all SimBlock out_ for t = t_n (n > 0).
   static void exeSimBlocks();

   static SimTime sim_time;

protected:
   const std::string blockType_;
   const ioType_t ioType_;
   int id_;
   std::vector<int> inputs_;
   double out_;

   virtual bool configDataIsOK(const SimBlock::configData_t & /*config*/) const
   {
      return true;
   }

   static std::map<int, SimBlock *> allSimBlocks_s;
   static std::vector<int> exeSequence_s;
};

} // namespace dysysim

#endif // SIMBLOCK_H
