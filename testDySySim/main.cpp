#include "DySySim.h"
#include "LibInfoDySySim.h"

#include <UnitTest++/UnitTest++.h>

#include <iostream>

namespace dss = dysysim;
using namespace std;

const double EPS{0.01};

SUITE(DySySim)
{
   TEST(Constant)
   {
      cout << "-- Constant" << endl;

      dss::SimTime::set(0.1, 0.3);

      dss::Log log;
      log.config({1, {2}, {}});

      dss::Constant con;
      double c = 3.0;
      con.config({2, {}, {c}});
      do {
         CHECK_CLOSE(c, con.output(), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(Attenuator)
   {
      cout << "-- Attenuator" << endl;

      dss::SimTime::set(1.0, 3.0);

      dss::Log log;
      log.config({1, {2, 3}, {}});

      dss::Attenuator att1;
      att1.config({2, {}, {10.0}});
      dss::Attenuator att2;
      att2.config({3, {}, {-10.0}});

      do {
         att1.input(1.0);
         CHECK_CLOSE(0.1, att1.output(), EPS);
         att2.input(1.0);
         CHECK_CLOSE(-0.1, att2.output(), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(Gain)
   {
      cout << "-- Gain" << endl;

      dss::SimTime::set(1.0, 3.0);

      dss::Gain gain1;
      gain1.config({2, {}, {10.0}});
      dss::Gain gain2;
      gain2.config({3, {}, {-5}});

      dss::Log log;
      log.config({1, {2, 3}, {}});

      do {
         gain1.input(1.0);
         CHECK_CLOSE(10.0, gain1.output(), EPS);
         gain2.input(-1.0);
         CHECK_CLOSE(5, gain2.output(), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(Limit)
   {
      cout << "-- Limit" << endl;

      dss::SimTime::set(1.0, 3.0);

      dss::Limit limit;
      limit.config({1, {}, {-10.0, 20.0}});

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
      onoff.config({2, {}, {off, on, on_off}});

      onoff.input(-1.0);
      CHECK_CLOSE(off, onoff.output(), EPS);
      onoff.input(0.0);
      CHECK_CLOSE(off, onoff.output(), EPS);
      onoff.input(1.5);
      CHECK_CLOSE(on, onoff.output(), EPS);
      onoff.input(10.0);
      CHECK_CLOSE(on, onoff.output(), EPS);
   }

   TEST(Time)
   {
      cout << "-- Time" << endl;
      const double delta_t{0.1};

      dss::SimTime::set(1.0, 3.0);

      dss::Time time;
      time.config({1, {}, {delta_t}});

      do {
         CHECK_CLOSE(dss::SimTime::t, time.output(), EPS);
      } while (dss::SimTime::simulation_on());
   }

   TEST(Step)
   {
      const double delta_t{0.1};

      dss::Time time;
      time.config({1, {}, {delta_t}});

      cout << "-- Step" << endl;

      dss::Step step;
      double off = 0.0;
      double on = 1.0;
      double t_on = 4 * delta_t;
      step.config({2, {}, {off, on, t_on}});

      CHECK_CLOSE(off, step.output(), EPS);
      time.exe();
      step.exe();
      CHECK_CLOSE(off, step.output(), EPS);
      time.exe();
      step.exe();
      CHECK_CLOSE(off, step.output(), EPS);
      time.exe();
      step.exe();
      CHECK_CLOSE(off, step.output(), EPS);
      time.exe();
      step.exe();
      CHECK_CLOSE(on, step.output(), EPS);
      time.exe();
      step.exe();
      CHECK_CLOSE(on, step.output(), EPS);
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
      puls.config({2, {}, {off, on, t_on, t_off}});

      dss::Log log;
      log.config({3, {2}, {}});

      while (dss::SimTime::t < t_on) {
         CHECK_CLOSE(off, puls.output(), EPS);
         dysysim::SimBlock::exeSimBlocks();
      }

      while (dss::SimTime::t >= t_on and dss::SimTime::t < t_off) {
         CHECK_CLOSE(on, puls.output(), EPS);
         dysysim::SimBlock::exeSimBlocks();
      }

      while (dss::SimTime::t >= t_off + (5 * delta_t)) {
         CHECK_CLOSE(off, puls.output(), EPS);
         dysysim::SimBlock::exeSimBlocks();
      }
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
      delay.config({3, {}, {0.0, delayTime}});

      CHECK_CLOSE(0.0, delay.output(), EPS);

      do {
         auto input = step.output();
         delay.input(input);
         if (dss::SimTime::t < t_on + delayTime) {
            CHECK_CLOSE(0.0, delay.output(), EPS);
         } else {
            CHECK_CLOSE(1.0, delay.output(), EPS);
         }
      } while (dss::SimTime::simulation_on());
   }

   // TEST(FirstOrder)
   // {
   //    const double delta_t{0.005};
   //    const double tau{100 * delta_t};
   //    const double stp{1.0};
   //    const double stp_t{5 * delta_t};

   //    dss::Time time;
   //    time.config({1, {}, {delta_t}});

   //    auto fio_response = [tau, stp_t, stp](double t) {
   //       return (t < stp_t) ? 0.0 : (stp * (1 - exp(-(t - stp_t) / tau)));
   //    };

   //    cout << "-- FirstOrder" << endl;

   //    dss::Step step;
   //    step.config({2, {}, {0.0, stp, stp_t}});

   //    dss::FirstOrder fio;
   //    fio.config({3, {}, {tau, 0.0}});

   //    while (time.output() < stp_t + 10 * tau) {
   //       auto input = step.output();
   //       fio.input(input);
   //       auto out1 = fio.output();
   //       auto out2 = fio_response(time.output());
   //       // std::cout << out1 << " == " << out2 << std::endl;

   //       CHECK_CLOSE(out1, out2, EPS);

   //       time.exe();
   //       step.exe();
   //    }
   // }

   //    TEST(RC_FirstOrder)
   //    {
   //       const double delta_t{0.005};
   //       const double tau{100 * delta_t};
   //       const double stp{1.0};
   //       const double stp_t{5 * delta_t};

   //       cout << "-- compare RC filter and FirstOrder" << endl;

   //       dss::Time time;
   //       time.config({0, {}, {delta_t}});

   //       dss::Step step;
   //       step.config({1, {}, {0.0, stp, stp_t}});

   //       dss::Attenuator att;
   //       att.config({2, {}, {tau}});

   //       dss::Integrator intgt;
   //       intgt.config({3, {}, {0.0}});

   //       dss::FirstOrder fio;
   //       fio.config({4, {}, {tau, 0.0}});

   //       while (time.output() < stp_t + 10 * tau) {
   //          auto input = step.output();

   //          att.input(input);
   //          att.input(step.output() - intgt.output());
   //          intgt.input(att.output());

   //          fio.input(input);

   //          auto out1 = intgt.output();
   //          auto out2 = fio.output();
   //          // std::cout << out1 << " == " << out2 << std::endl;

   //          CHECK_CLOSE(out1, out2, EPS);

   //          time.exe();
   //          step.exe();
   //       }
   //    }
}

int main()
{
   cout << "\n== Tests DySySim lib: " << dss::libVersion << " "
        << string(50, '=') << "\n\n";

   auto result = UnitTest::RunAllTests();

   cout << "\n" << string(80, '=') << endl;

   return result;
}
