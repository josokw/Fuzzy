#include "Builder.h"

dysysim::Builder::Builder()
{
   init();
}

void dysysim::Builder::operator()(std::ifstream &script)
{
   std::string line;
   while (std::getline(script, line)) {
      scriptLines_.push_back(line);
   }
   for (auto &line : scriptLines_) {
      parser_(line);
   }
}

void dysysim::Builder::init()
{
   factory_.init();
}
