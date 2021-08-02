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
      // Check for id != -1 (is SimBlock)
      if (std::get<0>(result) != -1) {
         std::cout << std::get<0>(result) << " " << std::get<1>(result) << "\n";
         SimBlock* pSB = factory_.create(std::get<1>(result));
      }
   }
}

void dysysim::Builder::execute()
{
   do {
      SimBlock::exeSimBlocks();
      SimTime::next();
   } while (SimTime::simulation_on());
}

void dysysim::Builder::init()
{
   factory_.init();
}
