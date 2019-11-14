#!/bin/sh
mkdir data-out
/usr/bin/g++ ./exe/calc.cpp -o ./exe/calc
./exe/calc
gnuplot -persist ./exe/plot.plt
open fig.ps
