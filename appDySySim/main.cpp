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

   if (programFile.is_open()) {
       std::cout << "\n-- Syntax check\n";
     builder(programFile);
   }
   std::cout << "\n";

   programFile.close();

   return 0;
}
