#!/bin/bash          
rm log_file.txt
#./sim leapfrog norender
mv log_file.txt leapfrog.txt
./sim jerk norender
mv log_file.txt jerk.txt
./sim jerk dynamic norender
mv log_file.txt jerk_dynamic.txt
./sim naive norender
mv log_file.txt naive.txt
./sim naive dynamic norender
mv log_file.txt naive_dynamic.txt


./sim naive norender timestep=0.001
mv log_file.txt naive.0_001.txt
./sim naive norender timestep=0.01
mv log_file.txt naive.0_01.txt
./sim naive norender timestep=0.1
mv log_file.txt naive.0_1.txt
./sim naive norender timestep=1
mv log_file.txt naive.1.txt

./sim leapfrog norender timestep=0.001
mv log_file.txt leapfrog.0_001.txt
./sim leapfrog norender timestep=0.01
mv log_file.txt leapfrog.0_01.txt
./sim leapfrog norender timestep=0.1
mv log_file.txt leapfrog.0_1.txt
./sim leapfrog norender timestep=1
mv log_file.txt leapfrog.1.txt
