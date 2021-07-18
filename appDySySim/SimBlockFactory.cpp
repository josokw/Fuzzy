#include "SimBlockFactory.h"
#include "DySySim.h"

void dysysim::SimBlockFactory::init()
{
   add("ATT", new dysysim::Attenuator);
   add("INT", new dysysim::Integrator);
   // add("PLS", new dysysim::Puls);

   std::cout << "-- SimBlockFactory size = " << size() << "\n";
}
