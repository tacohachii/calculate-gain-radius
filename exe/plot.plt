#!/ usr / local / bin / gnuplot - persist
set terminal postscript noenhanced color dashed defaultplex "Helvetica" 14
set out './fig.ps'
set xlabel "timeafterbounce[s]"
set ylabel "r[km]"
set title "Calculation result of formula (9) [the gain radius]"
set xrange [0:1]
set yrange [0:250]
set mxtics 2
set mytics 5
offset = 10
plot "./data-out/s12.out" using 5:6 with lines title "s12"
replot "./data-out/s15s7b2.out" using 5:($6 + 3 * offset) with lines title "s15s7b2"
replot "./data-out/s22.out" using 5:($6 + 6 * offset) with lines title "s22"
replot "./data-out/s25.out" using 5:($6 + 9 * offset) with lines title "s25"
set output
#EOF
