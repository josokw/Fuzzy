#include "DySySim.h"
#include "LibInfoDySySim.h"
#include "SimBlock.h"
#include "SimBlockFactory.h"

#include <UnitTest++/UnitTest++.h>

#include <iostream>

namespace dss = dysysim;
using namespace std;

const double EPS{0.02};

inline double getOutput(int id)
{
   return dss::SimBlock::getSimBlock(id)->output();
}

SUITE(DySySim)
{
   TEST(Constant)
   {
      cout << "-- Constant" << endl;

      dss::SimTime::set(1.0, 4.0);
      dss::SimBlockFactory sbf;
      sbf.init();
      sbf.configCheck("LOG", {1, {2}, {}});
      double c = 3.0;
      sbf.configCheck("CON", {2, {}, {c}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      do {
         CHECK_CLOSE(c, getOutput(2), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(Summator)
   {
      cout << "-- Summator" << endl;

      dss::SimBlockFactory sbf;
      sbf.init();
      dss::SimTime::set(1.0, 4.0);
      sbf.configCheck("LOG", {1, {2, 3, 4, 5}, {}});
      sbf.configCheck("CON", {2, {}, {1.0}});
      sbf.configCheck("CON", {3, {}, {-2.0}});
      sbf.configCheck("CON", {4, {}, {-2.0}});
      sbf.configCheck("SUM", {5, {2, 3, -4}, {}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      do {
         CHECK_CLOSE(1.0, getOutput(5), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(Attenuator)
   {
      cout << "-- Attenuator" << endl;

      dss::SimBlockFactory sbf;
      sbf.init();
      dss::SimTime::set(1.0, 4.0);
      sbf.configCheck("LOG", {1, {2, 3, 4}, {}});
      sbf.configCheck("CON", {2, {}, {1.0}});
      sbf.configCheck("ATT", {3, {2}, {10.0}});
      sbf.configCheck("ATT", {4, {2}, {-10.0}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      do {
         CHECK_CLOSE(0.1, getOutput(3), EPS);
         CHECK_CLOSE(-0.1, getOutput(4), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(Gain)
   {
      cout << "-- Gain" << endl;

      dss::SimBlockFactory sbf;
      sbf.init();
      dss::SimTime::set(1.0, 4.0);
      sbf.configCheck("CON", {1, {}, {1.0}});
      sbf.configCheck("GAIN", {2, {1}, {10.0}});
      sbf.configCheck("GAIN", {3, {1}, {-5.0}});
      sbf.configCheck("LOG", {4, {1, 2, 3}, {}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      do {
         CHECK_CLOSE(10.0, getOutput(2), EPS);
         CHECK_CLOSE(-5, getOutput(3), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(Time)
   {
      cout << "-- Time" << endl;

      dss::SimBlockFactory sbf;
      sbf.init();
      const double delta_t{0.1};
      dss::SimTime::set(delta_t, 1.0);
      sbf.configCheck("TIME", {1, {}, {}});
      sbf.configCheck("LOG", {2, {1}, {}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      CHECK_CLOSE(0.0, getOutput(1), EPS);
      do {
         CHECK_CLOSE(dss::SimTime::t, getOutput(1), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(Integrator)
   {
      cout << "-- Integrator" << endl;

      dss::SimBlockFactory sbf;
      sbf.init();
      dss::SimTime::set(0.01, 1.0);
      double c = 1.0;
      sbf.configCheck("CON", {1, {}, {c}});
      sbf.configCheck("INT", {2, {1}, {0.0}});
      sbf.configCheck("LOG", {3, {1, 2}, {}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      do {
         CHECK_CLOSE(dss::SimTime::t * getOutput(1), getOutput(2), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(Limit)
   {
      cout << "-- Limit" << endl;

      dss::SimBlockFactory sbf;
      sbf.init();
      dss::SimTime::set(1.0, 3.0);

      dss::Constant con;
      double c = 1.0;
      con.config({1, {}, {c}});

      dss::Limit limit;
      limit.config({2, {1}, {-10.0, 20.0}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      do {
         limit.input(0.0);
         CHECK_CLOSE(0.0, limit.output(), EPS);
         limit.input(-12.0);
         CHECK_CLOSE(-10.0, limit.output(), EPS);
         limit.input(22.0);
         CHECK_CLOSE(20.0, limit.output(), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(OnOff)
   {
      cout << "-- OnOff" << endl;

      dss::OnOff onoff;
      double off = -2.0;
      double on = 2.0;
      double on_off = 1.0;
      // OnOff has no input from other block (use id 0).
      onoff.config({1, {0}, {off, on, on_off}});

      onoff.input(-1.0);
      CHECK_CLOSE(off, onoff.output(), EPS);
      onoff.input(0.0);
      CHECK_CLOSE(off, onoff.output(), EPS);
      onoff.input(1.5);
      CHECK_CLOSE(on, onoff.output(), EPS);
      onoff.input(10.0);
      CHECK_CLOSE(on, onoff.output(), EPS);
   }

   TEST(Step)
   {
      cout << "-- Step" << endl;

      dss::SimBlockFactory sbf;
      sbf.init();
      const double delta_t{0.1};
      dss::SimTime::set(delta_t, 10 * delta_t);
      double off = -22.0;
      double on = 11.0;
      double t_on = 4 * delta_t;
      sbf.configCheck("STP", {1, {}, {off, on, t_on}});
      sbf.configCheck("LOG", {2, {1}, {}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      CHECK_CLOSE(off, getOutput(1), EPS);
      do {
         if (dss::SimTime::t < 4 * delta_t) {
            CHECK_CLOSE(off, getOutput(1), EPS);
         } else {
            CHECK_CLOSE(on, getOutput(1), EPS);
         }
      } while (dss::SimTime::simulation_on());
   }

   TEST(Puls)
   {
      cout << "-- Puls" << endl;

      dss::SimBlockFactory sbf;
      sbf.init();
      const double delta_t{0.1};
      dss::SimTime::set(delta_t, 10 * delta_t);
      double off = 0.0;
      double on = 1.0;
      double t_on = 5 * delta_t;
      double t_off = 10 * delta_t;
      sbf.configCheck("PLS", {1, {}, {off, on, t_on, t_off}});
      sbf.configCheck("LOG", {2, {1}, {}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      CHECK_CLOSE(0.0, getOutput(1), EPS);
      do {
         if (dss::SimTime::t < t_on) {
            CHECK_CLOSE(off, getOutput(1), EPS);
         }
         if (dss::SimTime::t >= t_on and dss::SimTime::t < t_off) {
            CHECK_CLOSE(on, getOutput(1), EPS);
         }
         if (dss::SimTime::t >= t_off + (5 * delta_t)) {
            CHECK_CLOSE(off, getOutput(1), EPS);
         }
      } while (dss::SimTime::simulation_on());
   }

   TEST(Delay)
   {
      cout << "-- Delay" << endl;

      dss::SimBlockFactory sbf;
      sbf.init();
      const double delta_t{0.1};
      const double delayTime{3 * delta_t};
      dss::SimTime::set(delta_t, 10 * delta_t);
      sbf.configCheck("LOG", {1, {2, 3}, {}});
      double t_on = 2 * delta_t;
      sbf.configCheck("STP", {2, {}, {0.0, 1.0, t_on}});
      sbf.configCheck("DLY", {3, {2}, {0.0, delayTime}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      CHECK_CLOSE(0.0, getOutput(3), EPS);
      do {
         if (dss::SimTime::t < t_on + delayTime) {
            CHECK_CLOSE(0.0, getOutput(3), EPS);
         } else {
            CHECK_CLOSE(1.0, getOutput(3), EPS);
         }
      } while (dss::SimTime::simulation_on());
   }

   TEST(FirstOrder)
   {
      cout << "-- FirstOrder" << endl;

      dss::SimBlockFactory sbf;
      sbf.init();
      const double delta_t{0.005};
      const double tau{10 * delta_t};
      const double stp{1.0};
      const double stp_t{5 * delta_t};
      dss::SimTime::set(delta_t, 6 * tau);
      auto fio_response = [tau, stp_t, stp](double t) {
         return (t < stp_t) ? 0.0 : (stp * (1 - exp(-(t - stp_t) / tau)));
      };

      sbf.configCheck("STP", {1, {}, {0.0, stp, stp_t}});
      sbf.configCheck("FIO", {2, {1}, {tau, 0.0}});
      sbf.configCheck("LOG", {3, {1, 2}, {}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      CHECK_CLOSE(0.0, getOutput(2), EPS);
      do {
         CHECK_CLOSE(getOutput(2), fio_response(dss::SimTime::t), EPS * 8);
      } while (dss::SimTime::simulation_on());
   }
}

int main()
{
   cout << "\n== Tests DySySim lib: " << dss::libVersion << " "
        << string(50, '=') << "\n\n";

   auto result = UnitTest::RunAllTests();

   cout << "\n" << string(80, '=') << endl;

   return result;
}
