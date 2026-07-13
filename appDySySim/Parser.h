#ifndef PARSER_H
#define PARSER_H

#include "DySySim.h"
#include "DySySimLogic.h"
#include "DySySimMath.h"

#include <boost/fusion/include/algorithm.hpp>
#include <boost/fusion/include/sequence.hpp>
#include <boost/fusion/include/vector.hpp>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <tuple>
#include <vector>

namespace dysysim {

class Builder;

void init_logger();

/// Parser parsers one line of DySySim code.
class Parser final
{
public:
   using id_t = int;
   using type_t = std::string;
   using value_t = double;
   using width_t = int;
   using precision_t = int;
   using result_t =
      std::tuple<id_t, type_t, std::vector<id_t>, std::vector<value_t>>;

   Parser(Builder &builder)
      : builder_{builder}
   {
      init_logger();
   }
   ~Parser() = default;

   result_t operator()(int lineNumber, std::string &codeLine);
   auto getSimParameters() const
   {
      return std::make_tuple(delta_t_, t_end_, width_t_, precision_t_);
   }

private:
   /// Remove single-line comment (C++ style).
   static void removeSingleLineComment(std::string &str);
   /// Remove leading and trailing whitespace.
   static void trim(std ::string &str, const std::string &whitespace);

private:
   Builder &builder_;

   bool simParametersAreSet_ = false;
   bool simBlocksAreSet_ = false;
   double delta_t_ = 0.0;
   double t_end_ = 0.0;
   width_t width_t_ = 10;
   precision_t precision_t_ = 3;

   Log logger_;

   unsigned int log_width_ = 0;
   unsigned int log_precision_ = 0;
};

} // namespace dysysim

#endif
