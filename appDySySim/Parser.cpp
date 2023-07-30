#include "Parser.h"
#include "Builder.h"
#include "Exceptions.h"
#include "SimBlock.h"

#include <iostream>

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

dysysim::Parser::result_t dysysim::Parser::operator()(int lineNumber,
                                                      std::string &codeLine)
{
   result_t result{-1, "", {}, {}};
   result_t result_LOG{0, "LOG", {}, {}};

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

   auto set_t_end = [this](auto &ctx) {
      SimTime::end_t = t_end_ = x3::_attr(ctx);
   };

   auto set_delta_t = [this](auto &ctx) {
      SimTime::delta_t = delta_t_ = x3::_attr(ctx);
   };

   auto set_width_t = [this](auto &ctx) { width_t_ = x3::_attr(ctx); };

   auto set_precision_t = [this](auto &ctx) { precision_t_ = x3::_attr(ctx); };

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

      auto set_sim_parameters = x3::lit("delta_t") >> x3::char_('=') >>
                                value[set_delta_t] >> x3::lit("t_end") >> '=' >>

                                value[set_t_end] >> x3::lit("width_t") >> '=' >>
                                value[set_width_t] >> x3::lit("precision_t") >>
                                '=' >> value[set_precision_t];

      auto set_simblock_parameters =
         id[set_id] >> type[set_type] >> *(inputs) >> *(set_parameter);

      auto set_log_parameters = ':' >> x3::uint_ >> x3::repeat(0, 2)[x3::uint_];

      if (simParametersAreSet_) {
         auto p = (x3::phrase_parse(iter, iterEnd, set_simblock_parameters,
                                    x3::space));

         if (not(p and iter == iterEnd)) {
            simBlocksAreSet_ = true;
            iter = codeLine.begin();
            iterEnd = codeLine.end();
            std::cout << "LOG = " << std::string(iter, iterEnd) << std::endl;

            auto plog =
               x3::phrase_parse(iter, iterEnd, *set_log_parameters, x3::space);
            if (not(plog and iter == iterEnd)) {
               std::cout << "--- ERROR LOG: " << plog << "="
                         << std::string(iter, iterEnd) << std::endl;
            }
            result = result_LOG;
         }
      } else {
         auto p =
            x3::phrase_parse(iter, iterEnd, set_sim_parameters, x3::space);

         if (not(p and iter == iterEnd)) {
            throw dysysim::SyntaxError(lineNumber, codeLine);
         }
         simParametersAreSet_ = true;
      }
   }

   return result;
}
