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

---
## DySySim

DySySim is a very basic [TUTSIM](http://tutsim.com/) look-a-like. TUTSIM was developed in the early 70's for script based simulation of time continuous systems represented in simulation blocks. 

Fuzzy is not (yet) implemented in DySySim.

### Simulating the response of a *RC network*

```
// Pulse response RC-network

delta_t = 0.005  t_end = 1.2  width_t = 5  precision_t = 1

1 PLS      off=0.0 on=1.0 t_on=0.1 t_off=0.3
2 ATT 1,-3 att=10.0    // RC time constant = 10 sec
3 INT 2    out_t0=0.0
```

### Simulating the response of a *Mass-Spring-Damper system*

```
// Mass-Spring-Damper system

delta_t = 0.02  t_end = 5.00  width_t = 4  precision_t = 2

1 PLS           off=0.0 on=25.0 t_on=0.1 t_off=1.1   // F = 25 N for 1 second
2 ATT 1,-5,-6   att=10                               // m = 10 kg
3 INT 2         out_t0=0.0                           // x'(0) = 0 m/s
4 INT 3         out_t0=0.0                           // x(0) = 0 m
5 GAIN 3        gain=30                              // r = 30N s/m
6 GAIN 4        gain=375                             // k = 375 N/m
7 LOG 1,4
```

Some output:

```
-- DySySim v0.6.0 -- uses libDySySim v0.21.0 -------------------------
-- SimBlockFactory 26 SimBlock types available.
[5]  1 PLS
[6]  2 ATT
[7]  3 INT
[8]  4 INT
[9]  5 GAIN
[10]  6 GAIN
[11]  7 LOG

---- DySySim simulation starts
0.00   1  PLS = 0.000   4  INT = 0.000  
0.02   1  PLS = 0.000   4  INT = 0.000  
0.04   1  PLS = 0.000   4  INT = 0.000  
0.06   1  PLS = 0.000   4  INT = 0.000  
0.08   1  PLS = 0.000   4  INT = 0.000  
0.10   1  PLS = 25.000   4  INT = 0.000  
0.12   1  PLS = 25.000   4  INT = 0.000  
0.14   1  PLS = 25.000   4  INT = 0.001  
0.16   1  PLS = 25.000   4  INT = 0.003  
0.18   1  PLS = 25.000   4  INT = 0.006  
0.20   1  PLS = 25.000   4  INT = 0.010  
0.22   1  PLS = 25.000   4  INT = 0.014  
0.24   1  PLS = 25.000   4  INT = 0.019  
0.26   1  PLS = 25.000   4  INT = 0.024  
0.28   1  PLS = 25.000   4  INT = 0.030  
0.30   1  PLS = 25.000   4  INT = 0.037  
0.32   1  PLS = 25.000   4  INT = 0.043  
0.34   1  PLS = 25.000   4  INT = 0.049  
0.36   1  PLS = 25.000   4  INT = 0.056  
0.38   1  PLS = 25.000   4  INT = 0.062  
0.40   1  PLS = 25.000   4  INT = 0.068  
0.42   1  PLS = 25.000   4  INT = 0.074  
0.44   1  PLS = 25.000   4  INT = 0.079  
0.46   1  PLS = 25.000   4  INT = 0.084  
0.48   1  PLS = 25.000   4  INT = 0.089  
0.50   1  PLS = 25.000   4  INT = 0.092  
0.52   1  PLS = 25.000   4  INT = 0.096  
0.54   1  PLS = 25.000   4  INT = 0.099  
0.56   1  PLS = 25.000   4  INT = 0.101  
0.58   1  PLS = 25.000   4  INT = 0.102  
0.60   1  PLS = 25.000   4  INT = 0.103  
0.62   1  PLS = 25.000   4  INT = 0.103  
0.64   1  PLS = 25.000   4  INT = 0.103  
0.66   1  PLS = 25.000   4  INT = 0.102  
0.68   1  PLS = 25.000   4  INT = 0.101  
0.70   1  PLS = 25.000   4  INT = 0.099  
0.72   1  PLS = 25.000   4  INT = 0.097  
0.74   1  PLS = 25.000   4  INT = 0.094  
0.76   1  PLS = 25.000   4  INT = 0.091  
0.78   1  PLS = 25.000   4  INT = 0.088  
0.80   1  PLS = 25.000   4  INT = 0.085  
0.82   1  PLS = 25.000   4  INT = 0.081  
0.84   1  PLS = 25.000   4  INT = 0.078  
0.86   1  PLS = 25.000   4  INT = 0.074  
0.88   1  PLS = 25.000   4  INT = 0.071  
0.90   1  PLS = 25.000   4  INT = 0.067  
0.92   1  PLS = 25.000   4  INT = 0.064  
0.94   1  PLS = 25.000   4  INT = 0.061  
0.96   1  PLS = 25.000   4  INT = 0.058  
0.98   1  PLS = 25.000   4  INT = 0.056  
1.00   1  PLS = 25.000   4  INT = 0.053  
1.02   1  PLS = 25.000   4  INT = 0.051  
1.04   1  PLS = 25.000   4  INT = 0.050  
1.06   1  PLS = 25.000   4  INT = 0.048  
1.08   1  PLS = 25.000   4  INT = 0.047  
1.10   1  PLS = 0.000   4  INT = 0.047  
1.12   1  PLS = 0.000   4  INT = 0.046  
1.14   1  PLS = 0.000   4  INT = 0.045  
1.16   1  PLS = 0.000   4  INT = 0.044  
1.18   1  PLS = 0.000   4  INT = 0.041  
1.20   1  PLS = 0.000   4  INT = 0.039  
1.22   1  PLS = 0.000   4  INT = 0.036  
1.24   1  PLS = 0.000   4  INT = 0.032  
1.26   1  PLS = 0.000   4  INT = 0.028  
1.28   1  PLS = 0.000   4  INT = 0.024  
1.30   1  PLS = 0.000   4  INT = 0.019  
 ...
 ```

Development, testing and debugging are in progress.
