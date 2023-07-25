#!/bin/bash

sim_name="FluPandemic"

simresult="sim"$sim_name".txt"

echo
echo ".. Start" $sim_name "simulation"
echo "..   data to $simresult"

../../bin/dss $sim_name.dss 2> $simresult
gnuplot -persist < plot.plt

echo ".. Ready" $sim_name "simulation"
echo
