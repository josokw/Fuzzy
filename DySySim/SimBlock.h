#ifndef SIMBLOCK_H
#define SIMBLOCK_H

#include <map>

namespace dysysim {

class CommonTime {
public:
   CommonTime() = default;
   ~CommonTime() = default;
   static void next() { t += TsimStep; }
   static double TsimStep;
   static double t;
};

class SimBlock {
public:
   SimBlock(int id): _id{id}, _out{0.0} { _allSimBlocks[id] = this; }
   SimBlock(int id, double initValue): _id{id}, _out{initValue} {}
   SimBlock(const SimBlock& other) = delete;
   SimBlock& operator=(const SimBlock& other) = delete;
   virtual ~SimBlock() = default;
   int getId() const { return _id; }
   double output() const { return _out; }
   static double getOutputSimBlock(int id) { return getSimBlock(id)->output(); }
protected:
   int _id;
   double _out;
   static std::map<int, SimBlock*> _allSimBlocks;
   static SimBlock* getSimBlock(int id) { return _allSimBlocks[id]; }
};

class TimedSimBlock: public SimBlock {
public:
   TimedSimBlock(int id): SimBlock{id} {}
   TimedSimBlock(int id, double initValue): SimBlock{id, initValue} {}
   virtual ~TimedSimBlock() = default;
protected:
   CommonTime tc;
};

}

#endif // SIMBLOCK_H
