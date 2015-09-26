#include "FuzzyLogic.h"
#include "InputFuzzySetTriangular.h"
#include "InputFuzzySetTrapezoidal.h"
#include "OutputFuzzySetTriangular.h"
#include "OutputFuzzySetTrapezoidal.h"
#include <unittest++/UnitTest++.h>
#include <iostream>

using namespace std;

SUITE(FuzzyEngine)
{
  TEST(mbs_InputFuzzySetTriangular)
  {
    cout << "-- InputFuzzySetTriangular mbs" << endl;
    InputFuzzySetTriangular ifz("Test", 5, 10, 15);
    ifz.setInput(2.5);
    CHECK_EQUAL(0.0, ifz.getMbs());
    ifz.setInput(7.5);
    CHECK_EQUAL(0.5, ifz.getMbs());
    ifz.setInput(12.5);
    CHECK_EQUAL(0.5, ifz.getMbs());
    ifz.setInput(15.0);
    CHECK_EQUAL(0.0, ifz.getMbs());
    ifz.setInput(17.5);
    CHECK_EQUAL(0.0, ifz.getMbs());
    cout << endl;
  }

  TEST(mbs_InputFuzzySetTrapezoidal)
  {
    cout << "-- InputFuzzySetTrapezoidal mbs" << endl;
    InputFuzzySetTrapezoidal ifz("Test", 0, 5, 10, 15);
    ifz.setInput(2.5);
    CHECK_EQUAL(0.5, ifz.getMbs());
    ifz.setInput(7.5);
    CHECK_EQUAL(1.0, ifz.getMbs());
    ifz.setInput(12.5);
    CHECK_EQUAL(0.5, ifz.getMbs());
    ifz.setInput(-5);
    CHECK_EQUAL(0.0, ifz.getMbs());
    cout << endl;
  }

  TEST(MOMsym_OutputFuzzySetTriangular)
  {
    cout << "-- OutputFuzzySetTriangular symmetrical MOM" << endl;
    OutputFuzzySetTriangular ofz("Test", 0, 5, 10);
    ofz.setMbs(0.5);
    CHECK_EQUAL(5.0, ofz.meanOfMaximum());
    ofz.setMbs(0.1);
    CHECK_EQUAL(5.0, ofz.meanOfMaximum());
    cout << endl;
  }

  TEST(MOM_OutputFuzzySetTriangular)
  {
    cout << "-- OutputFuzzySetTriangular not symmetrical MOM" << endl;
    OutputFuzzySetTriangular ofz("Test", 0, 10, 30);
    ofz.setMbs(0.5);
    CHECK_EQUAL(25.0 / 2, ofz.meanOfMaximum());
    cout << endl;
  }

  TEST(MOMsym_OutputFuzzySetTrapezoidal)
  {
    cout << "-- OutputFuzzySetTrapezoidal symmetrical MOM" << endl;
    OutputFuzzySetTrapezoidal ifz("Test", 0, 5, 10, 15);
    ifz.setMbs(0.5);
    CHECK_EQUAL(7.5, ifz.meanOfMaximum());
    ifz.setMbs(0.1);
    CHECK_EQUAL(7.5, ifz.meanOfMaximum());
    cout << endl;
  }

  TEST(MOM_OutputFuzzySetTrapezoidal)
  {
    cout << "-- OutputFuzzySetTrapezoidal not symmetrical MOM" << endl;
    OutputFuzzySetTrapezoidal ifz("Test", 0, 10, 20, 40);
    ifz.setMbs(0.5);
    CHECK_EQUAL(35.0 / 2, ifz.meanOfMaximum());
    cout << endl;
  }

  TEST(FuzzyLogic_or)
  {
    cout << "-- Fuzzy logic OR" << endl;
    InputFuzzySetTriangular ifz1("Test", 5, 10, 15);
    InputFuzzySetTriangular ifz2("Test", 10, 15, 20);
    OutputFuzzySetTriangular ofz("Test", 0, 5, 10);
    ifz1.setInput(12.5);
    ifz2.setInput(12.5);
    ofz = ifz1 or ifz2;
    CHECK_EQUAL(0.5, ofz.getMbs());
    cout << endl;
  }

  TEST(FuzzyLogic_and)
  {
    cout << "-- Fuzzy logic AND" << endl;
    InputFuzzySetTriangular ifz1("Test", 5, 10, 15);
    InputFuzzySetTriangular ifz2("Test", 10, 15, 20);
    OutputFuzzySetTriangular ofz("Test", 0, 5, 10);
    ifz1.setInput(10);
    ifz2.setInput(10);
    ofz = ifz1 and ifz2;
    CHECK_EQUAL(0, ofz.getMbs());
    cout << endl;
  }

  TEST(FuzzyLogic_not)
  {
    cout << "-- Fuzzy logic NOT" << endl;
    InputFuzzySetTriangular ifz1("Test", 5, 10, 15);
    InputFuzzySetTriangular ifz2("Test", 10, 15, 20);
    OutputFuzzySetTriangular ofz("Test", 0, 5, 10);
    ifz1.setInput(12.5);
    ifz2.setInput(12.5);
    ofz = not(ifz1 or ifz2);
    CHECK_EQUAL(0.5, ofz.getMbs());
    cout << endl;
  }


}

int main()
{
  auto result = UnitTest::RunAllTests();
  cout << endl;
  return result;
}
