#include "Defuzzification.h"
#include "FuzzyLogic.h"
#include "InputFuzzySetTrapezoidal.h"
#include "InputFuzzySetTriangular.h"
#include "OutputFuzzySetTrapezoidal.h"
#include "OutputFuzzySetTriangular.h"

#include <UnitTest++/UnitTest++.h>

#include <iostream>

const double EPS{0.01};

SUITE(FuzzyEngine)
{
   TEST(mbs_InputFuzzySetTriangular)
   {
      std::cout << "--- mbs_InputFuzzySetTriangular" << std::endl;
      InputFuzzySetTriangular ifz("Test", 5, 10, 20);

      ifz.setInput(-10.0);
      auto mbs = ifz.getMbs();
      CHECK_CLOSE(0.0, mbs, EPS);

      ifz.setInput(0.0);
      mbs = ifz.getMbs();
      CHECK_CLOSE(0.0, mbs, EPS);

      ifz.setInput(2.5);
      mbs = ifz.getMbs();
      CHECK_CLOSE(0.0, mbs, EPS);

      ifz.setInput(5.0);
      mbs = ifz.getMbs();
      CHECK_CLOSE(0.0, mbs, EPS);

      ifz.setInput(7.5);
      mbs = ifz.getMbs();
      CHECK_CLOSE(0.5, mbs, EPS);

      ifz.setInput(10.0);
      mbs = ifz.getMbs();
      CHECK_CLOSE(1.0, mbs, EPS);

      ifz.setInput(15.0);
      mbs = ifz.getMbs();
      CHECK_CLOSE(0.5, mbs, EPS);

      ifz.setInput(20.0);
      mbs = ifz.getMbs();
      CHECK_CLOSE(0.0, mbs, EPS);

      ifz.setInput(25.0);
      mbs = ifz.getMbs();
      CHECK_CLOSE(0.0, mbs, EPS);
      std::cout << std::endl;
   }

   TEST(mbs_InputFuzzySetTrapezoidal)
   {
      std::cout << "--- mbs_InputFuzzySetTrapezoidal" << std::endl;
      InputFuzzySetTrapezoidal ifz("Test", 5, 10, 20, 40);

      ifz.setInput(-10.0);
      auto mbs = ifz.getMbs();
      CHECK_CLOSE(0.0, mbs, EPS);

      ifz.setInput(0.0);
      mbs = ifz.getMbs();
      CHECK_CLOSE(0.0, mbs, EPS);

      ifz.setInput(2.5);
      mbs = ifz.getMbs();
      CHECK_CLOSE(0.0, mbs, EPS);

      ifz.setInput(5.0);
      mbs = ifz.getMbs();
      CHECK_CLOSE(0.0, mbs, EPS);

      ifz.setInput(7.5);
      mbs = ifz.getMbs();
      CHECK_CLOSE(0.5, mbs, EPS);

      ifz.setInput(10.0);
      mbs = ifz.getMbs();
      CHECK_CLOSE(1.0, mbs, EPS);

      ifz.setInput(15.0);
      mbs = ifz.getMbs();
      CHECK_CLOSE(1.0, mbs, EPS);

      ifz.setInput(20.0);
      mbs = ifz.getMbs();
      CHECK_CLOSE(1.0, mbs, EPS);

      ifz.setInput(30.0);
      mbs = ifz.getMbs();
      CHECK_CLOSE(0.5, mbs, EPS);

      ifz.setInput(40.0);
      mbs = ifz.getMbs();
      CHECK_CLOSE(0.0, mbs, EPS);

      ifz.setInput(50.0);
      mbs = ifz.getMbs();
      CHECK_CLOSE(0.0, mbs, EPS);
      std::cout << std::endl;
   }

   TEST(defuz_OutputFuzzySetTriangular)
   {
      std::cout << "--- defuz_OutputFuzzySetTriangular" << std::endl;
      OutputFuzzySetTriangular ofz("Test", 5, 10, 20);

      ofz.setMbs(0.5);
      CHECK_CLOSE(7.5, ofz.firstOfMaxima(), EPS);
      CHECK_CLOSE(15.0, ofz.lastOfMaxima(), EPS);
      CHECK_CLOSE((7.5 + 15.0) / 2.0, ofz.meanOfMaximum(), EPS);

      ofz.setMbs(0.1);
      CHECK_CLOSE(5.5, ofz.firstOfMaxima(), EPS);
      CHECK_CLOSE(11.0, ofz.lastOfMaxima(), EPS);
      CHECK_CLOSE((5.5 + 11.0) / 2.0, ofz.meanOfMaximum(), EPS);
      std::cout << std::endl;
   }

   TEST(defuz_OutputFuzzySetTrapezoidal)
   {
      std::cout << "-- defuz_OutputFuzzySetTrapezoidal" << std::endl;
      OutputFuzzySetTrapezoidal ofz("Test", 0, 5, 10, 20);

      ofz.setMbs(0.5);
      CHECK_CLOSE(5.0, ofz.firstOfMaxima(), EPS);
      CHECK_CLOSE(10.0, ofz.lastOfMaxima(), EPS);
      CHECK_CLOSE(7.5, ofz.meanOfMaximum(), EPS);

      ofz.setMbs(0.1);
      CHECK_CLOSE(5.0, ofz.firstOfMaxima(), EPS);
      CHECK_CLOSE(10.0, ofz.lastOfMaxima(), EPS);
      CHECK_CLOSE(7.5, ofz.meanOfMaximum(), EPS);
      std::cout << std::endl;
   }

   TEST(defuz_outputsFuzzySets)
   {
      std::cout << "-- defuz output Fuzzy Sets" << std::endl;
      OutputFuzzySetTrapezoidal ofz1("Test", 0, 1, 4, 5);
      OutputFuzzySetTrapezoidal ofz2("Test", 3, 4, 6, 7);
      OutputFuzzySetTrapezoidal ofz3("Test", 5, 6, 7, 8);
      std::array<OutputFuzzySet *, 3> all{&ofz1, &ofz2, &ofz3};

      ofz1.setMbs(0.3);
      ofz2.setMbs(0.5);
      ofz3.setMbs(1.0);
      CHECK_CLOSE(6.0, defuzFirstOfMaxima<3>(all), EPS);
      CHECK_CLOSE(6.5, defuzMeanOfMaximum<3>(all), EPS);
      CHECK_CLOSE(7.0, defuzLastOfMaxima<3>(all), EPS);
      CHECK_CLOSE(5.416, defuzWeightedAverage<3>(all), EPS);
      std::cout << std::endl;
   }

   TEST(FuzzyLogic_or)
   {
      std::cout << "-- Fuzzy logic OR" << std::endl;
      InputFuzzySetTriangular ifz1("Test", 5, 10, 15);
      InputFuzzySetTriangular ifz2("Test", 10, 15, 20);
      OutputFuzzySetTriangular ofz("Test", 0, 5, 10);

      ifz1.setInput(12.5);
      ifz2.setInput(12.5);
      ofz = ifz1 or ifz2;
      CHECK_CLOSE(0.5, ofz.getMbs(), EPS);
      std::cout << std::endl;
   }

   TEST(FuzzyLogic_and)
   {
      std::cout << "-- Fuzzy logic AND" << std::endl;
      InputFuzzySetTriangular ifz1("Test", 5, 10, 15);
      InputFuzzySetTriangular ifz2("Test", 10, 15, 20);
      OutputFuzzySetTriangular ofz("Test", 0, 5, 10);

      ifz1.setInput(10);
      ifz2.setInput(10);
      ofz = ifz1 and ifz2;
      CHECK_CLOSE(0.0, ofz.getMbs(), EPS);
      std::cout << std::endl;
   }

   TEST(FuzzyLogic_not)
   {
      std::cout << "-- Fuzzy logic NOT" << std::endl;
      InputFuzzySetTriangular ifz("Test", 5, 10, 15);
      OutputFuzzySetTriangular ofz("Test", 0, 5, 10);

      ifz.setInput(13.75);
      ofz = not ifz;
      CHECK_CLOSE(0.75, ofz.getMbs(), EPS);

      ifz.setInput(20);
      ofz = not ifz;
      CHECK_CLOSE(1.0, ofz.getMbs(), EPS);
      std::cout << std::endl;
   }
}

int main()
{
   auto result = UnitTest::RunAllTests();
   std::cout << std::endl;
   return result;
}