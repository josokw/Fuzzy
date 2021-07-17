#ifndef BUILDER_H
#define BUILDER_H

#include "Parser.h"
#include "SimBlockFactory.h"

namespace dysysim {

/// Builder parsers input and creates ...
/// \todo Implement Builder
class Builder final
{
public:
   using id_t = int;

   Builder() = default;

private:
   Parser parser_;
   SimBlockFactory factory_;
};

} // namespace dysysim

#endif
