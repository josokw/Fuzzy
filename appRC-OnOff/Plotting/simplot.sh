#!/bin/bash

sim_name="RC-OnOff"

simresult="sim"$sim_name".txt"

echo
echo ".. Start" $sim_name "simulation"
echo "..   data to $simresult"

../../bin/$sim_name $simresult
gnuplot -persist < plot.plt

echo ".. Ready" $sim_name "simulation"
echo

