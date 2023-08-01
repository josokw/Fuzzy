#ifndef DYSYSIMCONTROL_H
#define DYSYSIMCONTROL_H

#include "SimBlock.h"

namespace dysysim {

class Hysteresis : public SimBlock
{
public:
   Hysteresis();
   ~Hysteresis() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Hysteresis>();
   }
   std::vector<std::error_code>
   config(const SimBlock::configData_t &config) override;
   void exe() override { input(sumInputs()); }
   void input(double in)
   {
      /// \todo implement
   }
   void reset()
   {
      out_ = out_t0_;
   }

private:
   double out_t0_;
   double hysteresis_;
   double slope_;

   std::vector<std::error_code>
   configDataIsOK(const SimBlock::configData_t &config) const override;
};

} // namespace dysysim

#endif
