#include "DySySim.h"
#include "LibInfoDySySim.h"
#include <unittest++/UnitTest++.h>
#include <iostream>

namespace dss = dysysim;
using namespace std;

const double EPS {0.0001};

SUITE(DySySim)
{
   TEST(Attenuator) {
      cout << "-- Attenuator" << endl;
      dss::Attenuator att{1, 10.0};
      att.input(1.0);
      CHECK_CLOSE(0.1, att.output(), EPS);
      att.input(-1.0);
      CHECK_CLOSE(-0.1, att.output(), EPS);
   }

   TEST(Gain) {
      cout << "-- Gain" << endl;
      dss::Gain gain{1, 10.0};
      gain.input(1.0);
      CHECK_CLOSE(10.0, gain.output(), EPS);
      gain.input(-1.0);
      CHECK_CLOSE(-10.0, gain.output(), EPS);
   }

   TEST(Time) {
      cout << "-- Time" << endl;
      dss::Time time{1, 0.1};
      CHECK_CLOSE(0.0, time.output(), EPS);
      time.next();
      CHECK_CLOSE(0.1, time.output(), EPS);
      time.next();
      CHECK_CLOSE(0.2, time.output(), EPS);
      for(int  i = 0; i < 10; ++i) {
         time.next();
      }
      CHECK_CLOSE(1.2, time.output(), EPS);
   }

   TEST(Step) {
      dss::Time time{1, 0.1};
      cout << "-- Step" << endl;
      dss::Step step{2, 0.0, 1.0, 0.3};
      CHECK_CLOSE(0.0, step.output(), EPS);
      time.next();
      step.next();
      CHECK_CLOSE(0.0, step.output(), EPS);
      time.next();
      step.next();
      CHECK_CLOSE(1.0, step.output(), EPS);
      time.next();
      step.next();
      CHECK_CLOSE(1.0, step.output(), EPS);
      time.next();
      step.next();
      CHECK_CLOSE(1.0, step.output(), EPS);
      time.next();
      step.next();
      CHECK_CLOSE(1.0, step.output(), EPS);
   }
}

int main() {
   cout << "\n== Tests DySySim lib: " << dss::libVersion
        << " " << string(50, '=') << endl << endl;

   auto result = UnitTest::RunAllTests();

   cout << endl << string(80, '=') << endl;

   return result;
}
