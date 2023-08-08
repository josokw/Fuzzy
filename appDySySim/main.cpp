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

      std::ifstream dssFile;

      if (argc != 2) {
         std::cerr << "Usage: " << APPNAME_VERSION
                   << " needs 1 dss file name as argument\n";
         return 1;
      }

      dssFile.open(argv[1]);

      if (dssFile.is_open()) {
         builder(dssFile);
      } else {
         std::cerr << "-- ERROR: file " << argv[1] << " not available"
                   << std::endl;
      }
      dssFile.close();
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
