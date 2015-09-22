#include "OutputFuzzySetTriangular.h"
#include "OutputFuzzySetTrapezoidal.h"
#include <unittest++/UnitTest++.h>
#include <iostream>

using namespace std;

SUITE(FuzzyEngine)
{
  TEST(OutputFuzzySetTriangular)
  {
    cout << "OutputFuzzySetTriangular symmetrical MOM\n";
    OutputFuzzySetTriangular ifz("Test", 0, 5, 10);
    ifz.setMbs(0.5);
    CHECK_EQUAL(5.0, ifz.meanOfMaximum());
    ifz.setMbs(0.1);
    CHECK_EQUAL(5.0, ifz.meanOfMaximum());
    cout << endl;
  }

  TEST(OutputFuzzySetTrapezoidal)
  {
    cout << "OutputFuzzySetTrapezoidal symmetrical MOM\n";
    OutputFuzzySetTrapezoidal ifz("Test", 0, 5, 10, 15);
    ifz.setMbs(0.5);
    CHECK_EQUAL(7.5, ifz.meanOfMaximum());
    ifz.setMbs(0.1);
    CHECK_EQUAL(7.5, ifz.meanOfMaximum());
    cout << endl;
  }
}

int main()
{
  return UnitTest::RunAllTests();
}
