#ifndef BUILDER_H
#define BUILDER_H

#include "Parser.h"
#include "SimBlockFactory.h"

#include <string>

namespace dysysim {

/// Builder parsers input stream text and creates ...
/// \todo implement input stream
class Builder final
{
public:
   Builder();

   Parser::result_t operator()(const std::string &codeLine);

private:
   SimBlockFactory factory_;
   Parser parser_;

   void init();
};

} // namespace dysysim

#endif
