#include "DySySim.h"
#include "LibInfoDySySim.h"
#include "SimBlock.h"

#include <UnitTest++/UnitTest++.h>

#include <iostream>

namespace dss = dysysim;
using namespace std;

const double EPS{0.02};

SUITE(DySySim)
{
   TEST(Constant)
   {
      cout << "-- Constant" << endl;

      dss::SimTime::set(1.0, 4.0);

      dss::Log log;
      log.config({1, {2}, {}});

      dss::Constant con;
      double c = 3.0;
      con.config({2, {}, {c}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      do {
         CHECK_CLOSE(c, con.output(), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(Summator)
   {
      cout << "-- Summator" << endl;

      dss::SimTime::set(1.0, 4.0);

      dss::Log log;
      log.config({1, {2, 3, 4, 5}, {}});

      dss::Constant con1;
      con1.config({2, {}, {1.0}});
      dss::Constant con2;
      con2.config({3, {}, {-2.0}});
      dss::Constant con3;
      con3.config({4, {}, {-2.0}});

      dss::Summator sum;
      sum.config({5, {2, 3, -4}, {}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      do {
         CHECK_CLOSE(1.0, sum.output(), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(Attenuator)
   {
      cout << "-- Attenuator" << endl;

      dss::SimTime::set(1.0, 4.0);

      dss::Log log;
      log.config({1, {2, 3, 4}, {}});

      dss::Constant con;
      double c = 1.0;
      con.config({2, {}, {c}});

      dss::Attenuator att1;
      att1.config({3, {2}, {10.0}});
      dss::Attenuator att2;
      att2.config({4, {2}, {-10.0}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      do {
         CHECK_CLOSE(0.1, att1.output(), EPS);
         CHECK_CLOSE(-0.1, att2.output(), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(Gain)
   {
      cout << "-- Gain" << endl;

      dss::SimTime::set(1.0, 4.0);

      dss::Constant con;
      double c = 1.0;
      con.config({1, {}, {c}});

      dss::Gain gain1;
      gain1.config({2, {1}, {10.0}});
      dss::Gain gain2;
      gain2.config({3, {1}, {-5}});

      dss::Log log;
      log.config({4, {1, 2, 3}, {}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      do {
         CHECK_CLOSE(10.0, gain1.output(), EPS);
         CHECK_CLOSE(-5, gain2.output(), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(Time)
   {
      cout << "-- Time" << endl;

      const double delta_t{0.1};

      dss::SimTime::set(delta_t, 1.0);

      dss::Time time;
      time.config({1, {}, {}});

      dss::Log log;
      log.config({2, {1}, {}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      CHECK_CLOSE(0.0, time.output(), EPS);
      do {
         CHECK_CLOSE(dss::SimTime::t, time.output(), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(Integrator)
   {
      cout << "-- Integrator" << endl;

      dss::SimTime::set(0.01, 1.0);

      dss::Constant con;
      double c = 1.0;
      con.config({1, {}, {c}});

      dss::Integrator integrator;
      integrator.config({2, {1}, {0.0}});

      dss::Log log;
      log.config({3, {1, 2}, {}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      do {
         CHECK_CLOSE(dss::SimTime::t * con.output(), integrator.output(), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(Limit)
   {
      cout << "-- Limit" << endl;

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

      dss::SimBlock::clearSimBlocks();

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
      const double delta_t{0.1};

      dss::SimTime::set(delta_t, 10 * delta_t);

      cout << "-- Step" << endl;

      dss::Step step;
      double off = -22.0;
      double on = 11.0;
      double t_on = 4 * delta_t;
      step.config({1, {}, {off, on, t_on}});

      dss::Log log;
      log.config({2, {1}, {}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      CHECK_CLOSE(off, step.output(), EPS);
      do {
         if (dss::SimTime::t < 4 * delta_t) {
            CHECK_CLOSE(off, step.output(), EPS);
         } else {
            CHECK_CLOSE(on, step.output(), EPS);
         }
      } while (dss::SimTime::simulation_on());
   }

   TEST(Puls)
   {
      const double delta_t{0.1};

      dss::SimTime::set(delta_t, 10 * delta_t);

      cout << "-- Puls" << endl;

      dss::Puls puls;
      double off = 0.0;
      double on = 1.0;
      double t_on = 5 * delta_t;
      double t_off = 10 * delta_t;
      puls.config({1, {}, {off, on, t_on, t_off}});

      dss::Log log;
      log.config({2, {1}, {}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      CHECK_CLOSE(0.0, puls.output(), EPS);
      do {
         if (dss::SimTime::t < t_on) {
            CHECK_CLOSE(off, puls.output(), EPS);
         }
         if (dss::SimTime::t >= t_on and dss::SimTime::t < t_off) {
            CHECK_CLOSE(on, puls.output(), EPS);
         }
         if (dss::SimTime::t >= t_off + (5 * delta_t)) {
            CHECK_CLOSE(off, puls.output(), EPS);
         }
      } while (dss::SimTime::simulation_on());
   }

   TEST(Delay)
   {
      const double delta_t{0.1};
      const double delayTime{3 * delta_t};

      dss::SimTime::set(delta_t, 10 * delta_t);

      cout << "-- Delay" << endl;

      dss::Log log;
      log.config({1, {2, 3}, {}});

      double t_on = 2 * delta_t;
      dss::Step step;
      step.config({2, {}, {0.0, 1.0, t_on}});

      dss::Delay delay;
      delay.config({3, {2}, {0.0, delayTime}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      CHECK_CLOSE(0.0, delay.output(), EPS);
      do {
         if (dss::SimTime::t < t_on + delayTime) {
            CHECK_CLOSE(0.0, delay.output(), EPS);
         } else {
            CHECK_CLOSE(1.0, delay.output(), EPS);
         }
      } while (dss::SimTime::simulation_on());
   }

   TEST(FirstOrder)
   {
      const double delta_t{0.005};
      const double tau{10 * delta_t};
      const double stp{1.0};
      const double stp_t{5 * delta_t};

      dss::SimTime::set(delta_t, 6 * tau);

      auto fio_response = [tau, stp_t, stp](double t) {
         return (t < stp_t) ? 0.0 : (stp * (1 - exp(-(t - stp_t) / tau)));
      };

      cout << "-- FirstOrder" << endl;

      dss::Step step;
      step.config({1, {}, {0.0, stp, stp_t}});

      dss::FirstOrder fio;
      fio.config({2, {1}, {tau, 0.0}});

      dss::Log log;
      log.config({3, {1, 2}, {}});

      dss::SimBlock::setExeSequence();
      dss::SimBlock::initSimBlocks();
      CHECK_CLOSE(0.0, fio.output(), EPS);
      do {
         CHECK_CLOSE(fio.output(), fio_response(dss::SimTime::t), EPS * 8);
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
