#!/bin/sh
rm ./exe/calc
rm fig.ps
rm -r data-out
mkdir data-out
/usr/bin/g++ ./exe/calc.cpp -o ./exe/calc
./exe/calc
gnuplot -persist ./exe/plot.plt
open fig.ps
