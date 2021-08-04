#ifndef SIMMODEL_H
#define SIMMODEL_H

#include "SimBlock.h"
#include "SimModelTime.h"

#include <map>

namespace dysysim {

// /// \todo Implement
// class SimModelLogger final
// {
// public:
//    SimModelLogger(std::map<int, SimBlock *> &model): model_{model} {};

//    void show()
//    {
//       std::cerr << " t = " << SimTime::t << "   ";
//       for (auto id : inputs_) {
//          auto pSB = SimBlock::getSimBlock(id);
//          std::cerr << id << " " << pSB->getBlockType() << " = " <<
//          pSB->output()
//                    << "  ";
//       }
//       std::cerr << "\n";
//    }

// private:
//    std::vector<int> inputs_;
//    std::map<int, SimBlock *> &model_;
// };

/// SimModel is responsible for the management of SimBlock object pointers.
/// \todo Implement
class SimModel final
{
public:
   SimModelTime sim_time;
   //    SimModelLogger sim_logger;

   SimModel() = default;
   ~SimModel() = default;

   //    void clear() { allSimBlocks_s.clear(); }
   //    SimBlock *getSimBlock(int id) { return allSimBlocks_s.at(id); }
   //    bool idIsUnique(int id);
   //    void init()
   //    {
   //       SimTime::reset();
   //       for (auto sb : allSimBlocks_s) {
   //          sb.second->init();
   //       }
   //    }
   //    /// Sort for correct simulation order.
   //    /// \todo Implement
   //    void sort() {}
   //    /// Executes full model 1 time step.
   //    void exe()
   //    {
   //       dysysim::SimTime::next();
   //       for (auto sb : allSimBlocks_s) {
   //          sb.second->exe();
   //       }
   //    }
   //    /// Executes all simulation steps
   //    /// \todo Add logging
   //    void start()
   //    {
   //       init();
   //       while (SimTime::simulation_on) {
   //          exe();
   //       }
   //    }

private:
   std::map<int, SimBlock *> allSimBlocks_;
};

} // namespace dysysim

#endif
