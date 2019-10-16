#!/bin/bash

simresult="simdata.txt"

echo
echo ".. Start RC-OnOff"
echo "..   to $simresult"
../../bin/RC-OnOff $simresult

gnuplot -persist < plot.plt

echo ".. Ready RC-OnOff"
echo

