# Fuzzy and DySySim (Dynamical Systems Simulator)

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/bf89c5a36cb9439182fa7d20216c0973)](https://www.codacy.com/project/josokw/Fuzzy/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=josokw/Fuzzy&amp;utm_campaign=Badge_Grade_Dashboard)
[![CodeFactor](https://www.codefactor.io/repository/github/josokw/fuzzy/badge)](https://www.codefactor.io/repository/github/josokw/fuzzy)

C++ FuzzyEngine library implemented.

## Build management by CMake

Update CMake to the latest version (pip command must be available):

    sudo apt remove cmake

    sudo pip install cmake --upgrade

Go to the Fuzzy directory:

    cd build
    cmake ..
    make

## DySySim parser and Unit testing

This project contains some unit tests for **Fuzzy** and **DySySim**.
Install the C++ [UnitTest++](https://github.com/unittest-cpp/unittest-cpp) library.

DySySim uses C++ [Boost Spirit X3](https://www.boost.org/doc/libs/develop/libs/spirit/doc/x3/html/index.html).

For creating diagrams [gnuplot](http://www.gnuplot.info) is used.

## Tipping problem

Tipping problem fuzzy rules, using the FuzzyEngine library code:

    IF service is poor OR food is rancid THEN tip is cheap
    IF service is good THEN tip is average
    IF service is excellent OR food is delicious THEN tip is generous with 0.5
    IF service is excellent AND food is delicious THEN tip is generous with 1.0

### Fuzzy sets definitions

    - TippingFIS v0.4.1 --------------------------------------------------

    Service = poor (0, 0, 2.5, 5)  input = 0  mbs = 0
    Service = good (2.5, 5, 7.5)  input = 0  mbs = 0
    Service = great (5, 7.5, 10, 10)  input = 0  mbs = 0
    Food = rancid (0, 0, 1.5, 4)  input = 0  mbs = 0
    Food = delicious (6, 8.5, 10, 10)  input = 0  mbs = 0
    Tip = cheap (0, 5, 10) mbs = 0
    Tip = average (10, 15, 20) mbs = 0
    Tip = generous (20, 25, 30) mbs = 0

### Zadeh logic

    not a = 1 - a
    a and b = min(a, b)
    a or b = max(a, b)

### Lukasiewicz logic

    not a = 1 - a
    a and b = max(a+b-1, 0)
    a or b = min(a+b, 1)

## Execute program

Current dir is *build*:

    ../bin/Tipping

Defuzzification example 1:

    -- Defuzzification: Weighted Average

    service

          10     11   11   12   16   25   25   25   25   25   25   25
           9     11   11   12   16   25   25   25   25   25   25   25
           8     11   11   12   16   25   25   25   25   25   25   25
           7     11   11   12   15   21   21   21   21   23   23   23
           6     10   10   11   13   17   17   17   19   19   19   19
           5     10   10   10   12   15   15   15   16   17   18   18
           4      8    8    9   11   11   11   11   13   15   15   15
           3      6    6    7    7    7    7    7   10   12   13   13
           2      5    5    5    5    5    5    5    8   10   11   11
           1      5    5    5    5    5    5    5    8   10   11   11
           0      5    5    5    5    5    5    5    8   10   11   11

        food      0    1    2    3    4    5    6    7    8    9   10

Defuzzification example 2 and 3:

    -- Defuzzification: Center of Sums, logic model: Zadeh

    service

          10     11   11   12   16   25   25   25   25   25   25   25
           9     11   11   12   16   25   25   25   25   25   25   25
           8     11   11   12   16   25   25   25   25   25   25   25
           7     11   11   12   15   21   21   21   21   23   23   23
           6     10   10   11   13   17   17   17   19   19   19   19
           5     10   10   10   12   15   15   15   16   17   18   18
           4      8    8    9   11   11   11   11   13   15   15   15
           3      6    6    7    7    7    7    7   10   12   13   13
           2      5    5    5    5    5    5    5    8   10   11   11
           1      5    5    5    5    5    5    5    8   10   11   11
           0      5    5    5    5    5    5    5    8   10   11   11

        food      0    1    2    3    4    5    6    7    8    9   10

    -- Defuzzification: Center of Sums, logic model: Lukasiewicz

     service

          10     11   11   12   16   25   25   25   25   25   25   25
           9     11   11   12   16   25   25   25   25   25   25   25
           8     11   11   12   16   25   25   25   25   25   25   25
           7     11   11   12   15   21   21   21   22   22   23   23
           6     10   10   11   13   17   17   17   19   19   19   19
           5     10   10   10   12   15   15   15   16   17   18   18
           4      8    8    8    9   11   11   11   13   15   15   15
           3      6    6    6    6    7    7    7   10   12   13   13
           2      5    5    5    5    5    5    5    8   10   11   11
           1      5    5    5    5    5    5    5    8   10   11   11
           0      5    5    5    5    5    5    5    8   10   11   11

        food      0    1    2    3    4    5    6    7    8    9   10

## DySySim

DySySim is a very basic [TUTSIM](http://tutsim.com/) look-a-like.
TUTSIM was developed in the early 70's for script based simulation of
time continuous systems.

Example DySySim script for simulating the response of a *RC network*:

    // Pulse response RC-network

    1 PLS      off=0.0 on=1.0 t_on=1.0 t_off=2.5
    2 ATT 1,-3 att=10.0    // RC time constant = 10 sec
    3 INT 2    out_t0=0.0

Development is in progress.
