#ifndef SIMBLOCKIO_H
#define SIMBLOCKIO_H

#include "SimBlockI.h"

namespace dysysim {

class SimBlockIO : public SimBlockI
{
public:
   SimBlockIO()
      : SimBlockI{}
      , out_{0.0}
   {
   }
   virtual ~SimBlockIO() = default;


   double output() const { return out_; }

protected:
   double out_;
};

class TimedSimBlockIO : public TimedSimBlockI
{
public:
   TimedSimBlockIO()
      : TimedSimBlockI{}
      , out_{0.0}
   {
   }
   virtual ~TimedSimBlockIO() = default;

   double output() const { return out_; }

protected:
   double out_;
};

} // namespace dysysim

#endif // SIMBLOCKIO_H
