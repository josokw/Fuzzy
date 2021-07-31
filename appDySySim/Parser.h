#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <tuple>
#include <vector>

namespace dysysim {

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
/// Example DySySim script 3 lines of code:
/// ```
/// 1 PLS      off=0.0 on=1.0 t_on=0.1 t_off=0.3
/// 2 ATT 1,-3 att=10.0
/// 3 INT 2    out_t0=0.0
/// ```
class Parser final
{
public:
   using id_t = int;
   using type_t = std::string;
   using value_t = double;
   using result_t =
      std::tuple<id_t, type_t, std::vector<id_t>, std::vector<value_t>>;

   Parser() = default;
   ~Parser() = default;

   result_t operator()(std::string &codeLine);

private:
   /// Remove single-line comment (C++ style).
   static void removeSingleLineComment(std::string &str);
   /// Remove leading and trailing whitespace.
   static void trim(std ::string &str, const std::string &whitespace);
};

} // namespace dysysim

#endif
