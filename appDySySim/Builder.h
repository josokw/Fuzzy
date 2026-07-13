#ifndef BUILDER_H
#define BUILDER_H

#include "Parser.h"
#include "SimBlockFactory.h"
#include "SimContext.h"

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

   SimContext &context() { return context_; }

private:
   SimContext context_;
   SimBlockFactory factory_;
   Parser parser_;
   std::vector<std::string> scriptLines_;
   int lineNumber_ = 0;

private:
   void initFactory();
};

} // namespace dysysim

#endif
