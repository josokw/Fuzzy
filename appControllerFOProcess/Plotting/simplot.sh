#!/bin/bash

simresult="simdata.txt"

echo
echo ".. Start ControllerFOProcess"
echo "..   to $simresult"
../../bin/ControllerFOProcess $simresult

gnuplot -persist < plot.plt

echo ".. Ready ControllerFOProcess"
echo

