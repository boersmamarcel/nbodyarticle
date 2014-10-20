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



set terminal pngcairo  transparent enhanced font "arial,16" fontscale 1.0 size 800,600
set output "euler_different_timesteps.png"
set xlabel "time"
set ylabel "relative energy error"
set title "euler integrator with different timesteps"
set datafile separator ","
plot "naive.0_001.txt" using 4:3 title "dt = 0.001" with line, \
         "naive.0_01.txt" using 4:3 title "dt = 0.01" with line, \
         "naive.0_1.txt" using 4:3 title "dt = 0.1" with line, \
         "naive.1.txt" using 4:3 title "dt = 1" with line
reset

set terminal pngcairo  transparent enhanced font "arial,16" fontscale 1.0 size 800,600
set output "leapfrog_different_timesteps.png"
set xlabel "time"
set ylabel "relative energy error"
set title "leapfrog integrator with different timesteps"
set datafile separator ","
plot "leapfrog.0_001.txt" using 4:3 title "dt = 0.001" with line, \
         "leapfrog.0_01.txt" using 4:3 title "dt = 0.01" with line, \
         "leapfrog.0_1.txt" using 4:3 title "dt = 0.1" with line, \
         "leapfrog.1.txt" using 4:3 title "dt = 1" with line
reset

