#include "Builder.h"
#include "SimBlock.h"

dysysim::Builder::Builder()
{
   init();
}

void dysysim::Builder::operator()(std::ifstream &script)
{
   SimBlock::clearSimBlocks();

   lineNumber_ = 0;
   std::string line;
   while (std::getline(script, line)) {
      scriptLines_.push_back(line);
   }
   for (auto &line : scriptLines_) {
      ++lineNumber_;
      auto result = parser_(line);
      auto [id, type, inputs, params] = result;
      SimBlock::configData_t cdata = {id, inputs, params};
      if (id != -1) {
         std::cerr << "[" << lineNumber_ << "]  " << id << " " << type << "\n";
         SimBlock *pSB = factory_.create(type);
         if (pSB) {
            pSB->config(cdata);
            SimBlock::addSimBlock(id, pSB);
         } else {
            std::cerr << "create() => pSB == nullptr\n";
         }
      }
   }
   std::vector<int> exeSequence{{1, 2, 3, 4}};
   SimBlock::setExeSequence(exeSequence);
   // SimBlock::setExeSequence();
   execute();
}

void dysysim::Builder::execute()
{
   auto [delta_t, t_end] =  parser_.getSimParameters();
   SimBlock::sim_time.delta_t = delta_t;
   SimBlock::sim_time.end_t = t_end;
   SimBlock::initSimBlocks();
   do {
      SimBlock::exeSimBlocks();
      // SimTime::next();
   } while (SimTime::simulation_on());
}

void dysysim::Builder::init()
{
   factory_.init();
}
