#!/usr/bin/env bash
mkdir -p ../tests/results
rm -f ../tests/results/*

./build.sh

../build/gites < ../tests/test1 > ../tests/results/test0_1_result
diff ../tests/wzor1 ../tests/results/test0_1_result > ../tests/results/test0_1_diff
 
if [ -d ../tests/example1 ]; then
    ../build/gites < ../tests/test1 > ../tests/results/test1_1_result
    diff ../tests/wzor1 ../tests/results/test1_1_result > ../tests/results/test1_1_diff
    ../build/gites < ../tests/test2 > ../tests/results/test1_2_result
    diff ../tests/wzor2 ../tests/results/test1_2_result > ../tests/results/test1_2_diff
    ../build/gites < ../tests/test3 > ../tests/results/test1_3_result
    diff ../tests/wzor3 ../tests/results/test1_3_result > ../tests/results/test1_3_diff
    ../build/gites < ../tests/test4 > ../tests/results/test1_4_result
    diff ../tests/wzor4 ../tests/results/test1_4_result > ../tests/results/test1_4_diff
    ../build/gites < ../tests/test5 > ../tests/results/test1_5_result
    diff ../tests/wzor5 ../tests/results/test1_5_result > ../tests/results/test1_5_diff
fi

if [ -d ../tests/example2 ]; then
    ../build/gites < ../tests/test1 > ../tests/results/test2_1_result
    diff ../tests/wzor1 ../tests/results/test2_1_result > ../tests/results/test2_1_diff
    ../build/gites < ../tests/test2 > ../tests/results/test2_2_result
    diff ../tests/wzor2 ../tests/results/test2_2_result > ../tests/results/test2_2_diff
    ../build/gites < ../tests/test3 > ../tests/results/test2_3_result
    diff ../tests/wzor3 ../tests/results/test2_3_result > ../tests/results/test2_3_diff
    ../build/gites < ../tests/test4 > ../tests/results/test2_4_result
    diff ../tests/wzor4 ../tests/results/test2_4_result > ../tests/results/test2_4_diff
    ../build/gites < ../tests/test5 > ../tests/results/test2_5_result
    diff ../tests/wzor5 ../tests/results/test2_5_result > ../tests/results/test2_5_diff
fi
