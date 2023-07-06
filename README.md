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
t      1  PLS   4  INT  
0.00     0.000     0.000  
0.02     0.000     0.000  
0.04     0.000     0.000  
0.06     0.000     0.000  
0.08     0.000     0.000  
0.10    25.000     0.000  
0.12    25.000     0.001  
0.14    25.000     0.003  
0.16    25.000     0.006  
0.18    25.000     0.010  
0.20    25.000     0.014  
0.22    25.000     0.019  
0.24    25.000     0.024  
0.26    25.000     0.030  
0.28    25.000     0.037  
0.30    25.000     0.043  
0.32    25.000     0.049  
0.34    25.000     0.056  
0.36    25.000     0.062  
0.38    25.000     0.068  
0.40    25.000     0.074  
0.42    25.000     0.079  
0.44    25.000     0.084  
0.46    25.000     0.089  
0.48    25.000     0.092  
0.50    25.000     0.096  
0.52    25.000     0.099  
0.54    25.000     0.101  
0.56    25.000     0.102  
0.58    25.000     0.103  
0.60    25.000     0.103  
0.62    25.000     0.103  
0.64    25.000     0.102  
0.66    25.000     0.101  
0.68    25.000     0.099  
0.70    25.000     0.097  
0.72    25.000     0.094  
0.74    25.000     0.091  
0.76    25.000     0.088  
0.78    25.000     0.085  
0.80    25.000     0.081  
0.82    25.000     0.078  
0.84    25.000     0.074  
0.86    25.000     0.071  
0.88    25.000     0.067  
0.90    25.000     0.064  
0.92    25.000     0.061  
0.94    25.000     0.058  
0.96    25.000     0.056  
0.98    25.000     0.053  
1.00    25.000     0.051  
1.02    25.000     0.050  
1.04    25.000     0.048  
1.06    25.000     0.047  
1.08    25.000     0.047  
1.10     0.000     0.046  
1.12     0.000     0.045  
1.14     0.000     0.044  
 ...
 ```

Development, testing and debugging are in progress.
