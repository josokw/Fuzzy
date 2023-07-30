#include "Builder.h"
#include "ErrorCodes.h"
#include "Exceptions.h"
#include "SimBlock.h"

dysysim::Builder::Builder()
   : parser_(*this)
{
   initFactory();
}

bool dysysim::Builder::operator()(std::ifstream &script)
{
   bool no_errors = true;

   try {
      SimBlock::clearSimBlocks();

      lineNumber_ = 0;
      std::string line;
      while (std::getline(script, line)) {
         scriptLines_.push_back(line);
      }

      for (auto &line : scriptLines_) {
         ++lineNumber_;
         auto result = parser_(lineNumber_, line);
         auto [id, type, inputs, params] = result;
         SimBlock::configData_t cdata = {id, inputs, params};
         if (id != -1) {
            auto erssnew = factory_.configCheck(type, cdata);
            if (erssnew.size()) {
               no_errors = false;
               for (auto er : erssnew) {
                  std::cerr << "[" << lineNumber_ << "] '" << line << "' "
                            << simblockErrCategory.message(er.value()) << "\n";
               }
            }
         }
      }
      // \todo  should be executed not here but ??
      if (no_errors) {
         SimBlock::setExeSequence();
         execute();
      }
   }
   catch (dysysim::FactoryAddError &e) {
      std::cerr << e.what() << ": " << e.getKey() << " is not unique\n";
   }
   catch (dysysim::FactoryUnknownTypeError &e) {
      std::cerr << e.what() << ": " << e.getType() << " is unknown\n";
   }

   return no_errors;
}

void dysysim::Builder::execute()
{
   auto [delta_t, t_end, width_t, precision_t] = parser_.getSimParameters();
   SimBlock::sim_time.delta_t = delta_t;
   SimBlock::sim_time.end_t = t_end;
   SimBlock::sim_time.width_t = width_t;
   SimBlock::sim_time.precision_t = precision_t;
   SimBlock::initSimBlocks();

   do {
      SimBlock::exeSimBlocks();
   } while (SimTime::simulation_on());
}

void dysysim::Builder::initFactory()
{
   factory_.init();
}
