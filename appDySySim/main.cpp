#include "AppInfo.h"
#include "LibInfoDySySim.h"

#include <boost/spirit/home/x3.hpp>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

namespace x3 = boost::spirit::x3;
namespace dss = dysysim;

int main(int argc, char *argv[])
{
   std::cout << "-- " APPNAME_VERSION " " << std::string(50, '-') << std::endl
             << "-- uses " + dss::libName + " v" << dss::libVersion << std::endl
             << std::endl;

   std::ifstream programFile;

   if (argc > 2) {
      return 1;
   }

   if (argc == 1) {
      programFile.open("../appDySySim/data/RCnetwork.dss");
   } else {
      programFile.open(argv[1]);
   }

   std::vector<std::string> program;

   if (programFile.is_open()) {
      std::string line;
      while (getline(programFile, line)) {
         program.push_back(line);
         std::cout << line << "\n";
      }
   }

   std::cout << "\n-- Syntax check\n";

   for (auto input : program) {
      auto iter = begin(input);
      auto iterEnd = end(input);

      auto value = x3::double_;
      auto c_name = x3::alpha >> *(x3::alnum | x3::char_('_'));
      auto set_const = c_name >> '=' >> value;
      auto input_indices = x3::int_ >> *(x3::char_(',') >> x3::int_);

      auto dssLine =
         x3::uint_ >> +x3::char_("A-Z") >> *input_indices >> *set_const;

      auto p = x3::phrase_parse(iter, iterEnd, dssLine, x3::space);

      std::cout << input
                << ((p and iter == iterEnd) ? "   OK  " : "   NOT OK  ")
                << "\n";
   }

   return 0;
}
