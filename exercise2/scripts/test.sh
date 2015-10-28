#!/usr/bin/env bash
mkdir -p ../tests/results
rm -f ../tests/results/*

./build.sh

../build/gites < ../tests/test1 > ../tests/results/test0_1_result
diff ../tests/wzor1 ../tests/results/test0_1_result > ../tests/results/test0_1_diff

# Allan, please add details