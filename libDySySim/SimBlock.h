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
   using configData_t = struct ConFigData {
      int id;
      std::vector<int> inputs;
      std::vector<double> parameters;
   };

   SimBlock()
      : id_{-1}
      , blockType_{""}
      , out_{0.0}
   {
   }
   SimBlock(const SimBlock &other) = delete;
   SimBlock &operator=(const SimBlock &other) = delete;
   virtual ~SimBlock() = default;

   virtual SimBlock *create() { return nullptr; }
   virtual void config(const configData_t &config) = 0;

   int getId() const { return id_; }
   const std::string &getBlockType() const { return blockType_; }

   /// Calculate out_ for t = 0
   virtual void init()
   {
      std::cerr << blockType_ << " --- init() NOT implemented\n";
   }
   double output() const { return out_; }
   /// Calculate out_ for t = t_n
   virtual void exe()
   {
      std::cerr << blockType_ << " --- exe() NOT implemented\n";
   }

   static void clearSimBlocks() { allSimBlocks_s.clear(); }
   static SimBlock *getSimBlock(int id) { return allSimBlocks_s.at(id); }
   static bool idIsUnique(int id);
   static void initSimBlocks();
   static void setExeSequence();
   static void setExeSequence(std::vector<int> &exeSequence);
   static void exeSimBlocks();

   static SimTime sim_time;

protected:
   int id_;
   std::string blockType_;
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
