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
  TEST(mbs_InputFuzzySetTriangular) {
    cout << "-- mbs_InputFuzzySetTriangular" << endl;
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

  TEST(mbs_InputFuzzySetTrapezoidal) {
    cout << "-- mbs_InputFuzzySetTrapezoidal" << endl;
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

  TEST(defuz_sym_OutputFuzzySetTriangular) {
    cout << "-- defuz_sym_OutputFuzzySetTriangular symmetrical" << endl;
    OutputFuzzySetTriangular ofz("Test", 0, 5, 10);

    ofz.setMbs(0.5);
    CHECK_EQUAL(5.0, ofz.meanOfMaximum());
    CHECK_EQUAL(0.0, ofz.firstOfMaxima());
    CHECK_EQUAL(10.0, ofz.lastOfMaxima());
    ofz.setMbs(0.1);
    CHECK_EQUAL(5.0, ofz.meanOfMaximum());
    CHECK_EQUAL(0.0, ofz.firstOfMaxima());
    CHECK_EQUAL(10.0, ofz.lastOfMaxima());
    cout << endl;
  }

  TEST(defuz_nosym_OutputFuzzySetTriangular)  {
    cout << "-- defuz_nosym_OutputFuzzySetTriangular" << endl;
    OutputFuzzySetTriangular ofz("Test", 0, 10, 30);

    ofz.setMbs(0.5);
    CHECK_EQUAL(25.0 / 2, ofz.meanOfMaximum());
    //CHECK_EQUAL(0.0, ofz.firstOfMaxima());
    //CHECK_EQUAL(30.0, ofz.lastOfMaxima());
    cout << endl;
  }

  TEST(defuz_sym_OutputFuzzySetTrapezoidal) {
    cout << "-- defuz_sym_OutputFuzzySetTrapezoidal" << endl;
    OutputFuzzySetTrapezoidal ofz("Test", 0, 5, 10, 15);

    ofz.setMbs(0.5);
    CHECK_EQUAL(7.5, ofz.meanOfMaximum());
    CHECK_EQUAL(5.0, ofz.firstOfMaxima());
    CHECK_EQUAL(10.0, ofz.lastOfMaxima());
    ofz.setMbs(0.1);
    CHECK_EQUAL(7.5, ofz.meanOfMaximum());
    CHECK_EQUAL(5.0, ofz.firstOfMaxima());
    CHECK_EQUAL(10.0, ofz.lastOfMaxima());
    cout << endl;
  }

  TEST(defuz_notsym_OutputFuzzySetTrapezoidal) {
    cout << "-- defuz_notsym_OutputFuzzySetTrapezoidal" << endl;
    OutputFuzzySetTrapezoidal ofz("Test", 0, 10, 20, 40);

    ofz.setMbs(0.5);
    CHECK_EQUAL(35.0 / 2, ofz.meanOfMaximum());
    //CHECK_EQUAL(0.0 / 2, ofz.firstOfMaxima());
    //CHECK_EQUAL(40.0 / 2, ofz.lastOfMaxima());
    cout << endl;
  }

  TEST(FuzzyLogic_or) {
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

  TEST(FuzzyLogic_and) {
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

  TEST(FuzzyLogic_not) {
    cout << "-- Fuzzy logic NOT" << endl;
    InputFuzzySetTriangular ifz("Test", 5, 10, 15);
    OutputFuzzySetTriangular ofz("Test", 0, 5, 10);

    ifz.setInput(13.75);
    ofz = not ifz;
    CHECK_EQUAL(0.75, ofz.getMbs());

    ifz.setInput(20);
    ofz = not ifz;
    CHECK_EQUAL(1.0, ofz.getMbs());
    cout << endl;
  }

}

int main() {
  auto result = UnitTest::RunAllTests();
  cout << endl;
  return result;
}
