#include "Parser.h"

#include <boost/spirit/home/x3.hpp>

namespace x3 = boost::spirit::x3;

dysysim::Parser::result_t
dysysim::Parser::operator()(const std::string &codeLine)
{
   auto f = [](auto &ctx) { std::cout << "SA " << x3::_attr(ctx) << "\n"; };

   auto iter = begin(codeLine);
   auto iterEnd = end(codeLine);

   auto value = x3::double_;
   auto c_name = x3::alpha >> *(x3::alnum | x3::char_('_'));
   auto set_const = c_name >> '=' >> value;
   auto input_indices = x3::int_[f] >> *(x3::char_(',') >> x3::int_[f]);

   auto dssLine = x3::uint_[f][f] >> (+x3::char_("A-Z"))[f] >>
                  *(input_indices) >> *set_const;

   auto p = x3::phrase_parse(iter, iterEnd, dssLine, x3::space);

   std::cout << codeLine
             << ((p and iter == iterEnd) ? "   OK  " : "   NOT OK  ") << "\n";

   return {1, "TEST", {2, 3}, {1.1, 2.22}};
}
