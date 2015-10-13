#!/usr/bin/env bash
mkdir -p ../Test_Results
rm -f ../Test_Results/*

./build.sh

../Build/gites < ../Test_Data/Example_1/test1 > ../Test_Results/test0_1_result
diff ../Test_Data/Example_0/wzor1 ../Test_Results/test0_1_result > ../Test_Results/test0_1_diff
 
if [ -d ../Test_Data/Example_1 ]; then
    ../Build/gites < ../Test_Data/Example_1/test1 > ../Test_Results/test1_1_result
    diff ../Test_Data/Example_1/wzor1 ../Test_Results/test1_1_result > ../Test_Results/test1_1_diff
    ../Build/gites < ../Test_Data/Example_1/test2 > ../Test_Results/test1_2_result
    diff ../Test_Data/Example_1/wzor2 ../Test_Results/test1_2_result > ../Test_Results/test1_2_diff
    ../Build/gites < ../Test_Data/Example_1/test3 > ../Test_Results/test1_3_result
    diff ../Test_Data/Example_1/wzor3 ../Test_Results/test1_3_result > ../Test_Results/test1_3_diff
    ../Build/gites < ../Test_Data/Example_1/test4 > ../Test_Results/test1_4_result
    diff ../Test_Data/Example_1/wzor4 ../Test_Results/test1_4_result > ../Test_Results/test1_4_diff
    ../Build/gites < ../Test_Data/Example_1/test5 > ../Test_Results/test1_5_result
    diff ../Test_Data/Example_1/wzor5 ../Test_Results/test1_5_result > ../Test_Results/test1_5_diff
fi

if [ -d ../Test_Data/Example_2 ]; then
    ../Build/gites < ../Test_Data/Example_2/test1 > ../Test_Results/test2_1_result
    diff ../Test_Data/Example_2/wzor1 ../Test_Results/test2_1_result > ../Test_Results/test2_1_diff
    ../Build/gites < ../Test_Data/Example_2/test2 > ../Test_Results/test2_2_result
    diff ../Test_Data/Example_2/wzor2 ../Test_Results/test2_2_result > ../Test_Results/test2_2_diff
    ../Build/gites < ../Test_Data/Example_2/test3 > ../Test_Results/test2_3_result
    diff ../Test_Data/Example_2/wzor3 ../Test_Results/test2_3_result > ../Test_Results/test2_3_diff
    ../Build/gites < ../Test_Data/Example_2/test4 > ../Test_Results/test2_4_result
    diff ../Test_Data/Example_2/wzor4 ../Test_Results/test2_4_result > ../Test_Results/test2_4_diff
    ../Build/gites < ../Test_Data/Example_2/test5 > ../Test_Results/test2_5_result
    diff ../Test_Data/Example_2/wzor5 ../Test_Results/test2_5_result > ../Test_Results/test2_5_diff
fi
