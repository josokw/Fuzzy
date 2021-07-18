#include "AppInfo.h"
#include "Builder.h"
#include "LibInfoDySySim.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

namespace dss = dysysim;

int main(int argc, char *argv[])
{
   std::cout << "-- " APPNAME_VERSION " " << std::string(50, '-') << std::endl
             << "-- uses " + dss::libName + " v" << dss::libVersion << std::endl
             << std::endl;

   dss::Builder builder;

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
      builder(input);
   }

   return 0;
}
