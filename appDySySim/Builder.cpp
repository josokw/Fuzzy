#include "Builder.h"

dysysim::Builder::Builder()
{
   init();
}

dysysim::Parser::result_t
dysysim::Builder::operator()(const std::string &codeLine)
{
   return parser_(codeLine);
}

void dysysim::Builder::init()
{
   factory_.init();
}
