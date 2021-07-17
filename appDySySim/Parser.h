#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <tuple>

namespace dysysim {

/// Parser parsers one line of DySySim code.
/// \todo Implement Parser.
class Parser final
{
public:
   using result_t = std::tuple<int, std::string, std::initializer_list<int>,
                               std::initializer_list<double>>;

   Parser() = default;
   ~Parser() = default;

   result_t operator()(const std::string &codeLine);

private:
};

} // namespace dysysim

#endif
