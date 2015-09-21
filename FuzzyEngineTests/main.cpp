#include "OutputFuzzySetTriangular.h"
#include <unittest++/UnitTest++.h>
#include <iostream>

using namespace std;

SUITE(classOutputFuzzySetTriangular)
{
  TEST(OutputFuzzySetTriangular)
  {
    cout << "OutputFuzzySet ctor\n";
    OutputFuzzySetTriangular ifz("Test", 0, 5, 10);
    ifz.setMbs(0.5);
    CHECK_EQUAL(ifz.meanOfMaximum(), 0.0);
    ifz.setMbs(0.5);
    CHECK_EQUAL(ifz.meanOfMaximum(), 0.5);
  }

//  TEST(telop)
//  {
//    cout << "Breuken telop ";
//    Breuk b1(1, 2);
//    Breuk b2(1, 2);
//    Breuk b3 = b1.telop(b2);

//    CHECK_EQUAL(b3.getTeller(), 1);
//    CHECK_EQUAL(b3.getNoemer(), 1);
//    cout << endl;
//  }
}

int main()
{
  return UnitTest::RunAllTests();
}
