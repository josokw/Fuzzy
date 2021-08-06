#include "SimBlockFactory.h"
#include "DySySim.h"

void dysysim::SimBlockFactory::init()
{
   add("ADL", new dysysim::AlgebraicDelay);
   add("ATT", new dysysim::Attenuator);
   add("CON", new dysysim::Constant);
   add("COS", new dysysim::Cos);
   add("DIV", new dysysim::Divider);
   add("DLY", new dysysim::Delay);
   add("EUL", new dysysim::IntegratorEuler);
   add("FIO", new dysysim::FirstOrder);
   add("FRQ", new dysysim::Frequency);
   add("GAIN", new dysysim::Gain);
   add("INT", new dysysim::Integrator);
   add("LIM", new dysysim::Limit);
   add("LOG", new dysysim::Log);
   add("MAX", new dysysim::Max);
   add("MIN", new dysysim::Min);
   add("MUL", new dysysim::Multiplier);
   add("ONOFF", new dysysim::OnOff);
   add("PI", new dysysim::PI);
   add("PID", new dysysim::PID);
   add("PLS", new dysysim::Puls);
   add("SIN", new dysysim::Sin);
   add("STP", new dysysim::Step);
   add("SUM", new dysysim::Summator);
   add("TIME", new dysysim::Time);
   add("ZOH", new dysysim::ZeroOrderHold);

   std::cout << "-- DySySim SimBlockFactory " << size()
             << " SimBlock types available.\n";
}
