set terminal pngcairo  transparent enhanced font "arial,16" fontscale 1.0 size 800,600
set output "constant_time.png"
set xlabel "time"
set ylabel "relative energy error"
set title "constant timestep integrators"
set datafile separator ","
plot "leapfrog.txt" using 4:(abs($3)) title "leapfrog" with line, \
         "jerk.txt" using 4:(abs($3)) title "jerk" with line, \
         "naive.txt" using 4:(abs($3)) title "euler" with line
reset

