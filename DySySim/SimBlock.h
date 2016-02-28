#ifndef SIMBLOCK_H
#define SIMBLOCK_H

#include <initializer_list>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>

namespace dysysim {

class SimTime {
public:
   SimTime() = default;
   ~SimTime() = default;
   static void reset() {
      t = 0.0;
   }
   static void next() {
      t += delta_t;
   }
   static double delta_t;
   static double t;
};

class SimBlock {
public:
   SimBlock(int id):
      _id{id}, _blockType{"SimBlock"} {
      _allSimBlocks[id] = this;
   }
   SimBlock(const SimBlock& other) = delete;
   SimBlock& operator=(const SimBlock& other) = delete;
   virtual ~SimBlock() = default;
   int getId() const {
      return _id;
   }
   const std::string& getBlockType() const {
      return _blockType;
   }
   static std::map<int, SimBlock*> getAllSimBlocks() {
      return _allSimBlocks;
   }
   static SimBlock* getSimBlock(int id) {
      return _allSimBlocks.at(id);
   }
protected:
   int _id;
   std::string _blockType;
   static std::map<int, SimBlock*> _allSimBlocks;
};

class TimedSimBlock: public SimBlock {
public:
   TimedSimBlock(int id):
      SimBlock{id} {
      _blockType = "Timed" + _blockType;
      _allSimBlocks[id] = this;
   }
   virtual ~TimedSimBlock() = default;
protected:
   SimTime sim_time;
};

}

#endif // SIMBLOCK_H
