#include "DySySim.h"
#include "LibInfoDySySim.h"

#include <UnitTest++/UnitTest++.h>

#include <iostream>

namespace dss = dysysim;
using namespace std;

const double EPS{0.01};

SUITE(DySySim)
{
   TEST(Attenuator)
   {
      cout << "-- Attenuator" << endl;

      dss::Attenuator att;
      att.config({1, {}, {10.0}});
      att.input(1.0);
      CHECK_CLOSE(0.1, att.output(), EPS);
      att.input(-1.0);
      CHECK_CLOSE(-0.1, att.output(), EPS);
   }

   TEST(Constant)
   {
      cout << "-- Constant" << endl;

      dss::Constant con;
      con.config({1, {}, {10.0}});
      CHECK_CLOSE(10.0, con.output(), EPS);
   }

   TEST(Gain)
   {
      cout << "-- Gain" << endl;

      dss::Gain gain;
      gain.config({1, {}, {10.0}});
      gain.input(1.0);
      CHECK_CLOSE(10.0, gain.output(), EPS);
      gain.input(-1.0);
      CHECK_CLOSE(-10.0, gain.output(), EPS);
   }

   TEST(Limit)
   {
      cout << "-- Limit" << endl;

      dss::Limit limit;
      limit.config({1, {}, {-10.0, 20.0}});
      limit.input(0.0);
      CHECK_CLOSE(0.0, limit.output(), EPS);
      limit.input(-12.0);
      CHECK_CLOSE(-10.0, limit.output(), EPS);
      limit.input(22.0);
      CHECK_CLOSE(20.0, limit.output(), EPS);
   }

   TEST(OnOff)
   {
      cout << "-- OnOff" << endl;

      dss::OnOff onoff;
      onoff.config({2, {}, {10, 1.0, 0.0}});
      onoff.input(-1.0);
      CHECK_CLOSE(0.0, onoff.output(), EPS);
      onoff.input(0.0);
      CHECK_CLOSE(0.0, onoff.output(), EPS);
      onoff.input(5.0);
      CHECK_CLOSE(0.0, onoff.output(), EPS);
      onoff.input(10.0);
      CHECK_CLOSE(1.0, onoff.output(), EPS);
      onoff.input(20.0);
      CHECK_CLOSE(1.0, onoff.output(), EPS);
   }

   TEST(Time)
   {
      cout << "-- Time" << endl;
      const double delta_t{0.1};

      dss::Time time;
      time.config({1, {}, {delta_t}});
      CHECK_CLOSE(0.0, time.output(), EPS);
      for (int i = 1; i < 10; ++i) {
         time.next();
         CHECK_CLOSE(i * delta_t, time.output(), EPS);
      }
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
      time.next();
      step.next();
      CHECK_CLOSE(off, step.output(), EPS);
      time.next();
      step.next();
      CHECK_CLOSE(off, step.output(), EPS);
      time.next();
      step.next();
      CHECK_CLOSE(off, step.output(), EPS);
      time.next();
      step.next();
      CHECK_CLOSE(on, step.output(), EPS);
      time.next();
      step.next();
      CHECK_CLOSE(on, step.output(), EPS);
   }

   TEST(Puls)
   {
      const double delta_t{0.1};

      dss::Time time;
      time.config({1, {}, {delta_t}});

      cout << "-- Puls" << endl;

      dss::Puls puls;
      double off = 0.0;
      double on = 1.0;
      double t_on = 5 * delta_t;
      double t_off = 10 * delta_t;
      puls.config({2, {}, {off, on, t_on, t_off}});

      CHECK_CLOSE(0.0, puls.output(), EPS);

      while (time() < t_on) {
         CHECK_CLOSE(off, puls.output(), EPS);
         time.next();
      }

      while (time() >= t_on and time() < t_off) {
         CHECK_CLOSE(on, puls.output(), EPS);
         time.next();
      }

      while (time() > t_off and time() < t_off + (5 * delta_t)) {
         CHECK_CLOSE(off, puls.output(), EPS);
         time.next();
      }
   }

   TEST(Delay)
   {
      const double delta_t{0.1};
      const double delayTime{3 * delta_t};

      dss::Time time;
      time.config({1, {}, {delta_t}});

      cout << "-- Delay" << endl;
      dss::Step step;
      step.config({2, {}, {0.0, 1.0, 2 * delta_t}});

      dss::Delay delay;
      delay.config({3, {}, {delayTime, 0.0}});

      for (int i = 0; i < 10; ++i) {
         auto input = step.output();
         delay.input(input);
         if (i < 5) {
            CHECK_CLOSE(0.0, delay.output(), EPS);
         } else {
            CHECK_CLOSE(1.0, delay.output(), EPS);
         }
         time.next();
         step.next();
      }
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

   //       time.next();
   //       step.next();
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

   //          time.next();
   //          step.next();
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
