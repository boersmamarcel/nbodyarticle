#!/bin/bash          
rm log_file.txt
./sim leapfrog norender
mv log_file.txt leapfrog.txt
./sim jerk norender
mv log_file.txt jerk.txt
#./sim jerk dynamic norender
#mv log_file.txt jerk_dynamic.txt
./sim naive norender
mv log_file.txt naive.txt
#./sim naive dynamic norender
#mv log_file.txt naive_dynamic.txt
