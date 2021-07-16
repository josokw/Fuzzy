#ifndef SIMBLOCKO_H
#define SIMBLOCKO_H

#include "SimBlock.h"

namespace dysysim {

class SimBlockO : public SimBlock
{
public:
   SimBlockO()
      : SimBlock{}
      , out_{0.0}
   {
   }
   SimBlockO(const SimBlockO &other) = delete;
   SimBlockO &operator=(const SimBlockO &other) = delete;
   virtual ~SimBlockO() = default;

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
   }

   double output() const { return out_; }
   // static double getOutputSimBlock(int id) { return
   // getSimBlock(id)->output(); }

protected:
   double out_;
};

class TimedSimBlockO : public TimedSimBlock
{
public:
   TimedSimBlockO()
      : TimedSimBlock{}
      , out_{0.0}
   {
   }
   virtual ~TimedSimBlockO() = default;

   void config(const SimBlock::configData_t config) override
   {
      id_ = config.id;
      if (SimBlock::allSimBlocks_s.find(id_) != end(SimBlock::allSimBlocks_s)) {
         SimBlock::allSimBlocks_s[id_] = this;
      }
      out_ = *begin(config.parameters);
   }

   double output() const { return out_; }

protected:
   const double initial_out_;
   double out_;
};

} // namespace dysysim

#endif // SIMBLOCKO_H
