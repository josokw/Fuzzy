#include "Builder.h"
#include "ErrorCodes.h"
#include "Exceptions.h"
#include "SimBlock.h"

dysysim::Builder::Builder()
   : factory_{context_}
   , parser_(*this)
{
   initFactory();
}

bool dysysim::Builder::operator()(std::ifstream &script)
{
   bool no_errors = true;

   try {
      context_.clear();

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
               for (const auto &er : erssnew) {
                  std::cerr << "[" << lineNumber_ << "] '" << line << "' "
                            << simblockErrCategory.message(er.value()) << "\n";
               }
            }
         }
      }
      if (no_errors) {
         auto err = context_.setExeSequence();
         if (!err) {
            no_errors = false;
            std::cerr << "setExeSequence() error: "
                      << simblockErrCategory.message(err.value()) << "\n";
            return no_errors;
         }
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
   context_.sim_time.set(delta_t, t_end);
   context_.sim_time.width_t = width_t;
   context_.sim_time.precision_t = precision_t;
   context_.initSimBlocks();

   while (context_.sim_time.simulation_is_on()) {
      context_.exeSimBlocks();
   }
}

void dysysim::Builder::initFactory()
{
   factory_.init();
}
