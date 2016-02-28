#ifndef SIMBLOCKIO_H
#define SIMBLOCKIO_H

#include "SimBlockI.h"

namespace dysysim {

class SimBlockIO: public SimBlockI
{
public:
   SimBlockIO(int id, std::initializer_list<int> ids):
      SimBlockI{id, ids} {
      _blockType += "O";
   }
   SimBlockIO(int id):
      SimBlockI{id, {}} {}
   virtual ~SimBlockIO() = default;
   double output() const {
      return _out;
   }
   virtual void next() const {}
protected:
   double _out;
};

class TimedSimBlockIO: public TimedSimBlockI {
public:
   TimedSimBlockIO(int id, double initial_out):
      TimedSimBlockI{id}, _initial_out{initial_out}, _out{initial_out} {
      _blockType = "Timed" + _blockType;
   }
   TimedSimBlockIO(int id):
      TimedSimBlockIO{id, 0.0} {}
   virtual ~TimedSimBlockIO() = default;
   double output() const {
      return _out;
   }
protected:
   const double _initial_out;
   double _out;
};

}

#endif // SIMBLOCKIO_H
