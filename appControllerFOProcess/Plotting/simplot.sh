#!/bin/bash

simresult="simdata.txt"

echo
echo ".. Start ControllerFOProcess"
echo "..   to $simresult"
../../FuzzyDebug/ControllerFOProcess/ControllerFOProcess ./simdata.txt

gnuplot -persist < plot.plt

echo ".. Ready ControllerFOProcess"
echo

