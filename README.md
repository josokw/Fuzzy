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
time continuous systems represented in simulation blocks.

Example DySySim script for simulating the response of a *RC network*:

```
// Pulse response RC-network

delta_t = 0.01    t_end = 1.0

1 PLS      off=0.0 on=1.0 t_on=0.1 t_off=0.3
2 ATT 1,-3 att=10.0    // RC time constant = 10 sec
3 INT 2    out_t0=0.0
```

Second script example for simulating a *Mass-Spring-Damper system*:

```
// Mass-Spring-Damper system

delta_t = 0.02   t_end = 5.00

1 PLS           off=0.0 on=25.0 t_on=0.1 t_off=1.1   // F = 25 N for 1 second
2 ATT 1,-5, -6  att=10                               // m = 10 kg
3 INT 2         out_t0=0.0                           // x'(0) = 0 m/s
4 INT 3         out_t0=0.0                           // x(0) = 0 m
5 GAIN 3        gain=30                              // r = 30N s/m
6 GAIN 4        gain=375                             // k = 375 N/m
7 LOG 1,4
```

Output:

```
-- DySySim v0.3.0 -- uses libDySySim v0.14.0 -------------------------
-- DySySim SimBlockFactory 25 SimBlock types available.
-- DySySim Builder syntax check:
''   OK
''   OK
'delta_t = 0.02   t_end = 9.75'   OK  
''   OK
'1 PLS           off=0.0 on=25.0 t_on=0.1 t_off=1.1'   OK  
'2 ATT 1,-5, -6  att=10'   OK  
'3 INT 2         out_t0=0.0'   OK  
'4 INT 3         out_t0=0.0'   OK  
'5 GAIN 3        gain=30'   OK  
'6 GAIN 4        gain=375'   OK  
'7 LOG 1,4'   OK  

---- DySySim simulation starts
 t = 0.000   1 PLS = 0.000   4 INT = 0.000   
 t = 0.020   1 PLS = 0.000   4 INT = 0.000   
 t = 0.040   1 PLS = 0.000   4 INT = 0.000   
 t = 0.060   1 PLS = 0.000   4 INT = 0.000   
 t = 0.080   1 PLS = 0.000   4 INT = 0.000   
 t = 0.100   1 PLS = 25.000   4 INT = 0.000   
 t = 0.120   1 PLS = 25.000   4 INT = 0.001   
 t = 0.140   1 PLS = 25.000   4 INT = 0.003   
 t = 0.160   1 PLS = 25.000   4 INT = 0.006   
 t = 0.180   1 PLS = 25.000   4 INT = 0.010   
 t = 0.200   1 PLS = 25.000   4 INT = 0.014   
 t = 0.220   1 PLS = 25.000   4 INT = 0.019   
 t = 0.240   1 PLS = 25.000   4 INT = 0.024   
 t = 0.260   1 PLS = 25.000   4 INT = 0.030   
 t = 0.280   1 PLS = 25.000   4 INT = 0.037   
 t = 0.300   1 PLS = 25.000   4 INT = 0.043   
 t = 0.320   1 PLS = 25.000   4 INT = 0.049   
 t = 0.340   1 PLS = 25.000   4 INT = 0.056   
 t = 0.360   1 PLS = 25.000   4 INT = 0.062   
 t = 0.380   1 PLS = 25.000   4 INT = 0.068   
 t = 0.400   1 PLS = 25.000   4 INT = 0.074   
 t = 0.420   1 PLS = 25.000   4 INT = 0.079   
 t = 0.440   1 PLS = 25.000   4 INT = 0.084   
 t = 0.460   1 PLS = 25.000   4 INT = 0.089   
 t = 0.480   1 PLS = 25.000   4 INT = 0.092   
 t = 0.500   1 PLS = 25.000   4 INT = 0.096   
 ...
 ```

Development, testing and debugging are in progress.
