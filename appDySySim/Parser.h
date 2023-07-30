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

/// Parser parsers one line of DySySim code.
///
/// Syntax line of code in PEG (Parsing Expression Grammer) notation
/// using Spirit parser x3 names (white space ignored x3::space)
/// for configuring a simulation block:
/// ``
/// id             <- x3::uint_
/// type           <- x3::alpha (x3::alnum / x3::char_('_'))*
/// value          <- x3::double_
/// parameter_name <- x3::alpha (x3::alnum / x3::char_('_'))*;
/// inputs         <- x3::int_ (x3::char_(',') x3::int_)*;
/// set_parameter  <- parameter_name '=' value;
///
/// codeline       <- id (inputs)* (set_parameter)*
/// ```
///
/// Example DySySim script 4 lines of code:
/// ```
/// 1 PLS      off=0.0 on=1.0 t_on=0.1 t_off=0.3
/// 2 ATT 1,-3 att=10.0
/// 3 INT 2    out_t0=0.0
/// 4 LOG 1,3  w=4 p=3  w=4 p=3
/// ```
/// In a DySySim script you can use single line comments like C++
/// and empty lines.
/// ```
/// // DySySim script example
///
/// 1 PLS      off=0.0 on=1.0 t_on=0.1 t_off=0.3
/// 2 ATT 1,-3 att=10.0    // time constant
/// 3 INT 2    out_t0=0.0
///
/// 4 LOG 1,3   w=4 p=3  w=4 p=3
///
/// The parameter names can be chosen arbitrarily.
/// ```
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

   uint log_width_ = 0;
   uint log_precision_ = 0;
};

} // namespace dysysim

#endif
