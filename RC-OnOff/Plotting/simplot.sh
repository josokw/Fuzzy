#!/bin/bash

simresult="simdata.txt"

echo
echo ".. Start RC-OnOff"
echo "..   to $simresult"
../../FuzzyDebug/RC-OnOff/RC-OnOff ./simdata.txt

gnuplot -persist < plot.plt

echo ".. Ready RC-OnOff"
echo

