#!/usr/bin/env bash
mkdir -p ../tests/results
rm -f ../tests/results/*

./build.sh

../build/gites < ../tests/test1 > ../tests/results/test1_result
diff ../tests/wzor1 ../tests/results/test1_result > ../tests/results/test1_diff

../build/gites < ../tests/test2 > ../tests/results/test2_result
diff ../tests/wzor2 ../tests/results/test2_result > ../tests/results/test2_diff

../build/gites < ../tests/test3 > ../tests/results/test3_result
diff ../tests/wzor3 ../tests/results/test3_result > ../tests/results/test3_diff

../build/gites < ../tests/test4 > ../tests/results/test4_result
diff ../tests/wzor4 ../tests/results/test4_result > ../tests/results/test4_diff

../build/gites < ../tests/test5 > ../tests/results/test5_result
diff ../tests/wzor5 ../tests/results/test5_result > ../tests/results/test5_diff
