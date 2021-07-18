#include "Parser.h"

#include <boost/spirit/home/x3.hpp>

namespace x3 = boost::spirit::x3;

dysysim::Parser::result_t
dysysim::Parser::operator()(const std::string &codeLine)
{
   result_t result{-1, "???", {}, {}};

   auto set_id = [&result](auto &ctx) {
      // std::cout << "ID = " << x3::_attr(ctx) << "\n";
      std::get<0>(result) = x3::_attr(ctx);
   };

   auto set_type = [&result](auto &ctx) {
      // std::cout << "Type = " << x3::_attr(ctx) << "\n";
      std::get<1>(result) = x3::_attr(ctx);
   };

   auto set_input = [&result](auto &ctx) {
      // std::cout << "Input = " << x3::_attr(ctx) << "\n";
      std::get<2>(result).push_back(x3::_attr(ctx));
   };

   auto set_param = [&result](auto &ctx) {
      // std::cout << "Param = " << x3::_attr(ctx) << "\n";
      std::get<3>(result).push_back(x3::_attr(ctx));
   };

   auto iter = begin(codeLine);
   auto iterEnd = end(codeLine);

   auto id = x3::uint_;
   auto type = (+x3::char_("A-Z"));
   auto value = x3::double_;
   auto parameter_name = x3::alpha >> *(x3::alnum | x3::char_('_'));
   auto inputs =
      x3::int_[set_input] >> *(x3::char_(',') >> x3::int_[set_input]);
   auto set_parameter = parameter_name >> '=' >> value[set_param];

   auto codeline =
      id[set_id] >> type[set_type] >> *(inputs) >> *(set_parameter);

   auto p = x3::phrase_parse(iter, iterEnd, codeline, x3::space);

   std::cout << "'" << codeLine << "'"
             << ((p and iter == iterEnd) ? "   OK  " : "   NOT OK  ") << "\n";

   return result;
}
