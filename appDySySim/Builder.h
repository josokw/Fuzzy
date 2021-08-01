#ifndef BUILDER_H
#define BUILDER_H

#include "Parser.h"
#include "SimBlockFactory.h"
#include "SimModel.h"

#include <fstream>
#include <string>
#include <vector>

namespace dysysim {

/// Builder parsers text input stream and creates executable model.
class Builder final
{
public:
   Builder();
   ~Builder() = default;

   /// Reads script, parsers every line.
   /// \todo Implement excutable result
   void operator()(std::ifstream &script);
   void execute();

private:
   SimBlockFactory factory_;
   Parser parser_;
   std::vector<std::string> scriptLines_;
   int lineNumber_ = 0;

   void init();
};

} // namespace dysysim

#endif
