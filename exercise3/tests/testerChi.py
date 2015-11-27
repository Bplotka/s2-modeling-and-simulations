#! /usr/bin/python

from subprocess import call, check_output
import scipy
from scipy.stats import chisquare

import time


UTIL_EXE = "../../exercise1/build/gites"
GENERATOR_EXE = "../build/generator"
MODULO = "4294967296"
BIT_SIZE = "30"
#    "../build/gites < ../tests/test1 > ../tests/results/test0_1_result"

def build():
    print "Compilation"
    call('cd ../../exercise1/scripts; bash ./build.sh; cd -', shell=True)
    call('cd ../scripts; bash ./build.sh; cd -', shell=True)
    print "...Programs compiled"

def test(generatorName, generatorType, seed, p, q, rangeBegin, rangeEnd, iterations, maxValue = long(MODULO)):
    meanTestValue = 0
    varTestValue = 0
    periodTestValue = 0
    chiValueA = 0
    chiValueB = 0
    range = rangeEnd - rangeBegin
    chiRange = maxValue / 10.0
    idealRange = range / 10.0

    print "--- started new test: " + generatorName
    for i in xrange(rangeBegin, rangeBegin + iterations):
        print str(i-rangeBegin) + "/" + str(iterations)
        with open(generatorName + ".out", 'w+') as outputFile:
            cmd = GENERATOR_EXE + " -t " + str(generatorType) + " -p " + str(p) + " -q " + str(q) + " -m " + MODULO + \
                " -s " + BIT_SIZE + " -b " + str(i) + " -e " + str(i+range) + " " + seed
            output = check_output(cmd, shell=True)

            arr = map(int, output.split(' ')[:-1])
            chiArr = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
            expChiArr = [idealRange, idealRange, idealRange, idealRange, idealRange, idealRange, idealRange, idealRange, idealRange, idealRange]
            for a in arr:
                hash = int(int(a) / int(chiRange))
                chiArr[hash] += 1

            print chiArr
            chiValue = chisquare(chiArr, expChiArr)
            chiValueA = chiValue[0]
            chiValueB = chiValue[1]

            outputFile.write(output)
            outputFile.flush()
            outputFile.close()

        # set precision 4 for exercise1 program
        cmd = UTIL_EXE + " 4 < " + generatorName + ".out"
        output = check_output(cmd, shell=True)

        splitted = output.split('\n')

        meanTestValue += float(splitted[0])
        varTestValue += float(splitted[1])
        periodTestValue += float(splitted[2])

    meanTestValue /= iterations
    varTestValue /= iterations
    periodTestValue /= iterations
    chiValueA /= iterations
    chiValueB /= iterations

    with open("ball.stats", 'a+') as statsFile:
        summary = "> " + generatorName + " -p " + str(p) + " -q " + str(q) + " -m " + MODULO + " -s " + BIT_SIZE + " -b " + \
                  str(rangeBegin) + " -e " + str(rangeBegin + range) + " " + seed + \
                  " [" + str(iterations) + "] Mean: " + str(meanTestValue) + "; Var: " + str(varTestValue) + \
                  "; Period: " + str(periodTestValue) + "; ChiValue (" + str(chiValueA) + "," + str(chiValueB) + ") \n"
        statsFile.write(summary)
        statsFile.flush()
        statsFile.close()


def scenario1():
    build()

    with open("ball.stats", 'a+') as statsFile:
            header = "---- New Scenario. MODULO: " + MODULO + "; BIT_SIZE: " + BIT_SIZE + " ---- \n"
            statsFile.write(header)
            statsFile.flush()
            statsFile.close()

    # for example: test("fibonacci", 1, "256 128 64 32 16", 5, 3, 256, 356, 100)
    test("fibonacci1", 1, "256 128 64 32 16", 5, 3, 256, 356, 10)
    test("fibonacci2", 1, "256 128 64 32 16 8", 6, 3, 256, 356, 10)

    test("t1", 2, "256", 5, 3, 256, 356, 10)
    test("t2", 2, "23424", 6, 3, 256, 356, 10)

    test("mix1", 3, "256 128 64 32 16", 5, 3, 256, 356, 10)
    test("mix2", 3, "256 128 64 32 16 8", 6, 3, 256, 356, 10)


def scenarioTau():
    build()

    with open("ball.stats", 'a+') as statsFile:
            header = "---- New Scenario. " + time.strftime("%Y-%m-%d %H:%M") \
                     + " Ranges! MODULO: " + MODULO + "; BIT_SIZE: " + BIT_SIZE + " ---- \n"
            statsFile.write(header)
            statsFile.flush()
            statsFile.close()

    test("bfibonacci", 1, "1717986916 234234234 2342 3 3 4  400000 2 2 2", 10, 3, 100, 400000, 1)
    test("tau11", 2, "131071", 16, 9, 0, 400000, 1, 1073741824)
    test("mix", 3, "123 1 1 2 3 5 8 13 21 34 55 89 144 233 377", 7, 3, 100, 400000, 1)
scenarioTau()
