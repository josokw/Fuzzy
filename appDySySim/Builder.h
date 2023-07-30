#ifndef BUILDER_H
#define BUILDER_H

#include "Parser.h"
#include "SimBlockFactory.h"
#include "SimModel.h"

#include <fstream>
#include <string>
#include <vector>

namespace dysysim {

/// Builder parsers text input stream, creates an executable model and executes
/// this builded model.
class Builder final
{
public:
   Builder();
   ~Builder() = default;

   /// Reads script, parses every line.
   bool operator()(std::ifstream &script);
   /// Executes simulation model.
   void execute();

private:
   SimBlockFactory factory_;
   Parser parser_;
   std::vector<std::string> scriptLines_;
   int lineNumber_ = 0;
   std::shared_ptr<SimBlock> pSimBlok_;
   
private:
   void initFactory();
};

} // namespace dysysim

#endif
