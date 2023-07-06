#include "AppInfo.h"
#include "Builder.h"
#include "Exceptions.h"
#include "LibInfoDySySim.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

namespace dss = dysysim;

int main(int argc, char *argv[])
{
   // std::cout << "-- " APPNAME_VERSION " "
   //           << "-- uses " + dss::libName + " v" << dss::libVersion << " "
   //           << std::string(25, '-') << "\n";

   try {
      dss::Builder builder;

      std::ifstream programFile;

      if (argc > 2) {
         return 1;
      }

      if (argc == 1) {
         programFile.open("../appDySySim/scripts/RCnetworkLog.dss");
      } else {
         programFile.open(argv[1]);
      }

      if (programFile.is_open()) {
         builder(programFile);
      }
      programFile.close();
   }
   catch (dss::FactoryAddError &e) {
      std::cerr << e.what() << ": " << e.getKey() << " is not unique\n";
   }
   catch (dss::SyntaxError &e) {
      std::cerr << e.what() << ": line [" << e.getLineNumber() << "] '"
                << e.getCodeLine() << "'\n";
   }
   catch (const std::exception &e) {
      std::cerr << e.what() << "\n";
   }
   catch (...) {
      std::cerr << "UNKNOWN ERROR\n";
   }

   return 0;
}
