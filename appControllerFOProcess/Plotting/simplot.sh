#!/bin/bash

simresult="simdata.txt"

echo
echo ".. Start ControllerFOProcess"
echo "..   to $simresult"
../bin/ControllerFOProcess $simresult

set term wxt
gnuplot -persist < Plotting//plot.plt

echo ".. Ready ControllerFOProcess"
echo

