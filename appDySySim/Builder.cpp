#include "Builder.h"
#include "Exceptions.h"
#include "SimBlock.h"

dysysim::Builder::Builder()
{
   initFactory();
   std::cout << "-- SimBlockFactory " << factory_.size()
             << " SimBlock types available.\n";
}

void dysysim::Builder::operator()(std::ifstream &script)
{
   try {
      SimBlock::clearSimBlocks();

      lineNumber_ = 0;
      std::string line;
      while (std::getline(script, line)) {
         scriptLines_.push_back(line);
      }
      std::cout << "-- DySySim Builder syntax check:\n";
      for (auto &line : scriptLines_) {
         ++lineNumber_;
         auto result = parser_(lineNumber_, line);
         auto [id, type, inputs, params] = result;
         SimBlock::configData_t cdata = {id, inputs, params};
         if (id != -1) {
            // std::cerr << "[" << lineNumber_ << "]  " << id << " " << type <<
            // "\n";
            SimBlock *pSB = factory_.create(type);
            if (pSB) {
               pSB->config(cdata);
            } else {
               std::cerr
                  << "---- DySySim ERROR simulation id create() => pSB == "
                     "nullptr\n";
            }
         }
      }
      SimBlock::setExeSequence();

      std::cout << "\n---- DySySim simulation starts\n";
      execute();
      std::cout << "\n";
   }
   catch (dysysim::FactoryInitError &e) {
      std::cerr << e.what() << ": " << e.getKey() << " is not unique\n";
   }
}

void dysysim::Builder::execute()
{
   auto [delta_t, t_end] = parser_.getSimParameters();
   SimBlock::sim_time.delta_t = delta_t;
   SimBlock::sim_time.end_t = t_end;
   SimBlock::initSimBlocks();
   do {
      SimBlock::exeSimBlocks();
   } while (SimTime::simulation_on());
}

void dysysim::Builder::initFactory()
{
   factory_.init();
}
