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
      dss::Attenuator att{1, 10.0};
      att.input(1.0);
      CHECK_CLOSE(0.1, att.output(), EPS);
      att.input(-1.0);
      CHECK_CLOSE(-0.1, att.output(), EPS);
   }

   TEST(Constant)
   {
      cout << "-- Constant" << endl;
      dss::Constant con{1, 10.0};
      CHECK_CLOSE(10.0, con.output(), EPS);
   }

   TEST(Gain)
   {
      cout << "-- Gain" << endl;
      dss::Gain gain{1, 10.0};
      gain.input(1.0);
      CHECK_CLOSE(10.0, gain.output(), EPS);
      gain.input(-1.0);
      CHECK_CLOSE(-10.0, gain.output(), EPS);
   }

   TEST(Limit)
   {
      cout << "-- Limit" << endl;
      dss::Limit limit{1, -10.0, 20.0};
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
      dss::OnOff onoff{2, 10, 1.0, 0.0};
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
      dss::Time time{1, delta_t};
      CHECK_CLOSE(0.0, time.output(), EPS);
      for (int i = 1; i < 10; ++i) {
         time.next();
         CHECK_CLOSE(i * delta_t, time.output(), EPS);
      }
   }

   TEST(Step)
   {
      const double delta_t{0.1};
      dss::Time time{1, delta_t};
      cout << "-- Step" << endl;
      dss::Step step{2, 0.0, 1.0, 4 * delta_t};
      CHECK_CLOSE(0.0, step.output(), EPS);
      time.next();
      step.next();
      CHECK_CLOSE(0.0, step.output(), EPS);
      time.next();
      step.next();
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
   }

   TEST(Delay)
   {
      const double delta_t{0.1};
      const double delayTime{3 * delta_t};
      dss::Time time{1, delta_t};
      cout << "-- Delay" << endl;
      dss::Step step{2, 0.0, 1.0, 2 * delta_t};
      dss::Delay delay{3, delayTime, 0.0};
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

   TEST(FirstOrder)
   {
      const double delta_t{0.005};
      const double tau{100 * delta_t};
      const double stp{1.0};
      const double stp_t{5 * delta_t};

      dss::Time time{1, delta_t};
      auto fio_response = [tau, stp_t, stp](double t) {
         return (t < stp_t) ? 0.0 : (stp * (1 - exp(-(t - stp_t) / tau)));
      };

      cout << "-- FirstOrder" << endl;

      dss::Step step{2, 0.0, stp, stp_t};
      dss::FirstOrder fio{3, tau, 0.0};

      while (time.output() < stp_t + 10 * tau) {
         auto input = step.output();
         fio.input(input);
         auto out1 = fio.output();
         auto out2 = fio_response(time.output());
         // std::cout << out1 << " == " << out2 << std::endl;
         if (time.output() < stp_t) {
            CHECK_CLOSE(0.0, out1, EPS);
         } else {
            CHECK_CLOSE(out1, out2, EPS);
         }
         time.next();
         step.next();
      }
   }

   TEST(RC_FirstOrder)
   {
      const double delta_t{0.005};
      const double tau{100 * delta_t};
      const double stp{1.0};
      const double stp_t{5 * delta_t};

      cout << "-- compare RC filter and FirstOrder" << endl;

      dss::Time time{0, delta_t};
      dss::Step step{1, 0.0, stp, stp_t};
      dss::Attenuator att{2, tau};
      dss::Integrator intgt{3, 0.0};

      dss::FirstOrder fio{4, tau, 0.0};

      while (time.output() < stp_t + 10 * tau) {
         auto input = step.output();

         att.input(input);
         att.input(step.output() - intgt.output());
         intgt.input(att.output());

         fio.input(input);

         auto out1 = intgt.output();
         auto out2 = fio.output();
         // std::cout << out1 << " == " << out2 << std::endl;

         CHECK_CLOSE(out1, out2, EPS);

         time.next();
         step.next();
      }
   }
}

int main()
{
   cout << "\n== Tests DySySim lib: " << dss::libVersion << " "
        << string(50, '=') << endl
        << endl;

   auto result = UnitTest::RunAllTests();

   cout << endl << string(80, '=') << endl;

   return result;
}
