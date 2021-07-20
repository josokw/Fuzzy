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

   static void reset() { t = 0.0; }
   static void next() { t += delta_t; }
   static double delta_t;
   static double t;
};

/// Abstract Base Class for all simulation block derived classes.
class SimBlock
{
public:
   using configData_t = struct ConFigData {
      int id;
      std::initializer_list<int> inputs;
      std::initializer_list<double> parameters;
   };

   SimBlock()
      : id_{-1}
      , blockType_{"???"}
   {
   }
   SimBlock(const SimBlock &other) = delete;
   SimBlock &operator=(const SimBlock &other) = delete;
   virtual ~SimBlock() = default;

   virtual SimBlock *create() { return nullptr; }
   virtual void config(const configData_t &config) = 0;

   int getId() const { return id_; }
   const std::string &getBlockType() const { return blockType_; }
   /// Calculate out
   virtual void exe() { std::cerr << "--- exe() NOT implemented\n"; }

   static void clearSimBlocks() { allSimBlocks_s.clear(); }
   static SimBlock *getSimBlock(int id) { return allSimBlocks_s.at(id); }
   static bool idIsUnique(int id);
   static void exeSimBlocks()
   {
      for (auto sb : allSimBlocks_s)
         sb.second->exe();
   }

protected:
   int id_;
   std::string blockType_;
   static std::map<int, SimBlock *> allSimBlocks_s;
};

/// Contains simulation time data.
class TimedSimBlock : public SimBlock
{
public:
   TimedSimBlock()
      : SimBlock{}
   {
      // blockType_ = "Timed" + blockType_;
      // _allSimBlocks[id] = this;
   }
   ~TimedSimBlock() override = default;

protected:
   SimTime sim_time;
};

} // namespace dysysim

#endif // SIMBLOCK_H
