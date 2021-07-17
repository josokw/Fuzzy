#ifndef SIMBLOCKIO_H
#define SIMBLOCKIO_H

#include "SimBlockI.h"

namespace dysysim {

class SimBlockIO : public SimBlockI
{
public:
   SimBlockIO()
      : SimBlockI{}
   {
   }
   virtual ~SimBlockIO() = default;

   // void config(const SimBlock::configData_t &config) override
   // {
   //    id_ = config.id;
   //    inputs_ = config.inputs;
   //    if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
   //       SimBlock::allSimBlocks_s[id_] = this;
   //    }
   // }

   double output() const { return out_; }
   virtual void next() const {}

protected:
   double out_;
};

class TimedSimBlockIO : public TimedSimBlockI
{
public:
   TimedSimBlockIO()
      : TimedSimBlockI{}
   {
   }
   virtual ~TimedSimBlockIO() = default;

   double output() const { return out_; }

protected:
   double out_;
};

} // namespace dysysim

#endif // SIMBLOCKIO_H
