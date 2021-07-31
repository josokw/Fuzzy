#include "Parser.h"

#include <boost/spirit/home/x3.hpp>

namespace x3 = boost::spirit::x3;

void dysysim::Parser::trim(std ::string &str, const std::string &whitespace)
{
   const auto strBegin = str.find_first_not_of(whitespace);
   if (strBegin == std::string::npos) {
      str.clear();
      return;
   }
   const auto strEnd = str.find_last_not_of(whitespace);
   const auto strRange = strEnd - strBegin + 1;

   str = str.substr(strBegin, strRange);
}

void dysysim::Parser::removeSingleLineComment(std::string &str)
{
   size_t pos{str.find("//")};
   if (pos != std::string::npos) {
      str.erase(pos);
   }
}

dysysim::Parser::result_t dysysim::Parser::operator()(std::string &codeLine)
{
   result_t result{-1, "", {}, {}};

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

   Parser::removeSingleLineComment(codeLine);
   Parser::trim(codeLine, " \t");

   if (!codeLine.empty()) {
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
                << ((p and iter == iterEnd) ? "   OK  " : "   NOT OK  ")
                << "\n";
   } else {
      std::cout << "''   OK\n";
   }

   return result;
}
