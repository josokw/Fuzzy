#ifndef SIMBLOCKO_H
#define SIMBLOCKO_H

#include "SimBlock.h"

namespace dysysim {

class SimBlockO: public SimBlock {
public:
   SimBlockO(int id, double initValue): SimBlock{id}, _out{initValue} {
      _blockType += "O";
   }
   SimBlockO(int id): SimBlockO(id, 0.0) {}
   SimBlockO(const SimBlockO& other) = delete;
   SimBlockO& operator=(const SimBlockO& other) = delete;
   virtual ~SimBlockO() = default;

   double output() const { return _out; }
   //static double getOutputSimBlock(int id) { return getSimBlock(id)->output(); }
protected:
   double _out;
};

class TimedSimBlockO: public TimedSimBlock {
public:
   TimedSimBlockO(int id, double initValue):
      TimedSimBlock{id}, _out{initValue} {
      _blockType += "O";
   }
   TimedSimBlockO(int id): TimedSimBlockO{id, 0.0} {}
   virtual ~TimedSimBlockO() = default;

   double output() const { return _out; }
protected:
   double _out;
};

}

#endif // SIMBLOCKO_H
