#ifndef SIMBLOCK_H
#define SIMBLOCK_H

#include <initializer_list>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>

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
   SimBlock(int id, double initValue): _id{id}, _out{initValue} {
      _allSimBlocks[id] = this;}
   SimBlock(int id): SimBlock(id, 0.0) {}
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

class Log: public SimBlock {
public:
   Log(std::initializer_list<int> ids): SimBlock{-1}, _ids{ids} {}
   void output() const {
      for (auto i: _ids) std::cout << i << ": " << getOutputSimBlock(i) << "  ";
      std::cout << std::endl;
   }
private:
   //std::ofstream _ofs;
   std::vector<int> _ids;
};

}

#endif // SIMBLOCK_H
