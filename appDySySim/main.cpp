#include "AppInfo.h"
#include "Builder.h"
#include "DySySim.h"
#include "LibInfoDySySim.h"
#include "Parser.h"
#include "SimBlockFactory.h"

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

   dss::Builder builder;
   dss::Parser parser;

   dss::SimBlockFactory sbf;

   sbf.add("ATT", new dss::Attenuator);

   std::cout << "  sbf size = " << sbf.size() << "\n";

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
      parser(input);
   }

   return 0;
}
