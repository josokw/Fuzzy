#include "DySySim.h"
#include <unittest++/UnitTest++.h>
#include <iostream>

namespace dss = dysysim;
using namespace std;

SUITE(DySySim)
{
   TEST(Attenuator) {
      cout << "-- Attenuator" << endl;
      dss::Attenuator att{1, 10.0};
      att.input(1.0);
      CHECK_EQUAL(0.1, att.output());
   }

   TEST(Gain) {
      cout << "-- Gain" << endl;
      dss::Gain gain{1, 10.0};
      gain.input(1.0);
      CHECK_EQUAL(10.0, gain.output());
   }

}

int main() {
   auto result = UnitTest::RunAllTests();
   cout << endl;
   return result;
}
