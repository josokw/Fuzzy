#ifndef SIMMODEL_H
#define SIMMODEL_H

// #include "SimBlock.h"

// #include <map>

// namespace dysysim {

// /// SimTime contains simulation time data.
// /// \todo Consider implementation as a struct?
// /// \todo Consider implementation t as std::chrono::...
// class SimTime final
// {
// public:
//    SimTime() = default;
//    ~SimTime() = default;

//    static double delta_t;
//    static double end_t;
//    static double t;

//    static void set(double delta, double end);
//    static double output() { return t; }
//    static void reset() { t = 0.0; }
//    static void next() { t += delta_t; }
//    static bool simulation_on();
// };

// /// \todo Implement
// class SimLogger final
// {
// public:
//    SimLogger(std::map<int, SimBlock *> &model): model_{model} {};

//    void show()
//    {
//       std::cerr << " t = " << SimTime::t << "   ";
//       for (auto id : inputs_) {
//          auto pSB = SimBlock::getSimBlock(id);
//          std::cerr << id << " " << pSB->getBlockType() << " = " << pSB->output()
//                    << "  ";
//       }
//       std::cerr << "\n";
//    }

// private:
//    std::vector<int> inputs_;
//    std::map<int, SimBlock *> &model_; 
// };

// /// Composite class for SimBlock objects.
// /// \todo Implement
// class SimModel final
// {
// public:
//    SimTime sim_time;
//    SimLogger sim_logger;

//    SimModel() = default;
//    ~SimModel() = default;

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
//       while (SimTime::simulation_on)
//       {
//          exe();
//       }
//    }

// private:
//    std::map<int, SimBlock *> allSimBlocks_s;
// };

// } // namespace dysysim

#endif
