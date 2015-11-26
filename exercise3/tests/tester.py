#! /usr/bin/python

from subprocess import call, check_output

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


def test(generatorName, generatorType, seed, p, q, rangeBegin, rangeEnd, iterations):
    meanTestValue = 0
    varTestValue = 0
    periodTestValue = 0
    range = rangeEnd - rangeBegin

    print "--- started new test: " + generatorName
    for i in xrange(rangeBegin, rangeBegin + iterations):
        print str(i-rangeBegin) + "/" + str(iterations)
        with open(generatorName + ".out", 'w+') as outputFile:
            cmd = GENERATOR_EXE + " -t " + str(generatorType) + " -p " + str(p) + " -q " + str(q) + " -m " + MODULO + \
                " -s " + BIT_SIZE + " -b " + str(i) + " -e " + str(i+range) + " " + seed
            output = check_output(cmd, shell=True)

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

    with open("all.stats", 'a+') as statsFile:
        summary = "> " + generatorName + " -p " + str(p) + " -q " + str(q) + " -m " + MODULO + " -s " + BIT_SIZE + " -b " + \
                  str(rangeBegin) + " -e " + str(rangeBegin + range) + " " + seed + \
                  " [" + str(iterations) + "] Mean: " + str(meanTestValue) + "; Var: " + str(varTestValue) + \
                  "; Period: " + str(periodTestValue) + "\n"
        statsFile.write(summary)
        statsFile.flush()
        statsFile.close()


def test_ranges(generatorName, generatorType, seed, p, q, rangeBegin, rangeEnd, packetSize):
    for i in xrange(rangeBegin, rangeEnd, packetSize):
        print str(i) + " - " + str(i + packetSize)
        test(generatorName, generatorType, seed, p, q, i, i + packetSize, 1)


def scenario1():
    build()

    with open("all.stats", 'a+') as statsFile:
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

def scenarioRangesFib():
    build()

    with open("all.stats", 'a+') as statsFile:
            header = "---- New Scenario. Ranges! MODULO: " + MODULO + "; BIT_SIZE: " + BIT_SIZE + " ---- \n"
            statsFile.write(header)
            statsFile.flush()
            statsFile.close()

    test_ranges("fibonacci", 1, "256 128 64 32 16", 5, 3, 0, 400000, 40000)


def scenarioRangesTau():
    build()

    with open("all.stats", 'a+') as statsFile:
            header = "---- New Scenario. Ranges! MODULO: " + MODULO + "; BIT_SIZE: " + BIT_SIZE + " ---- \n"
            statsFile.write(header)
            statsFile.flush()
            statsFile.close()

    test_ranges("tau", 2, "256 128 64 32 16", 5, 3, 0, 400000, 40000)

scenarioRangesTau()
