#! /usr/bin/python

from subprocess import call, check_output

UTIL_EXE = "../../exercise1/build/gites"
GENERATOR_EXE = "../build/generator"
MODULO = "4294967296"
BIT_SIZE = "32"
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
    allIterations = 0

    for i in xrange(rangeBegin, rangeBegin + iterations):
        print str(i-rangeBegin) + "/" + str(iterations)
        for j in xrange(rangeEnd, rangeEnd + iterations):
            with open(generatorName + ".out", 'w+') as outputFile:
                cmd = GENERATOR_EXE + " -t " + str(generatorType) + " -p " + str(p) + " -q " + str(q) + " -m " + MODULO + \
                    " -s " + BIT_SIZE + " -b " + str(i) + " -e " + str(j) + " " + seed
                output = check_output(cmd, shell=True)

                outputFile.write(output)
                outputFile.flush()
                outputFile.close()


            cmd = UTIL_EXE + " 4 < " + generatorName + ".out"
            output = check_output(cmd, shell=True)

            splitted = output.split('\n')

            meanTestValue += float(splitted[0])
            varTestValue += float(splitted[1])
            periodTestValue += float(splitted[2])

            allIterations += 1

    meanTestValue /= allIterations
    varTestValue /= allIterations
    periodTestValue /= allIterations

    with open("all.stats", 'a+') as statsFile:
        summary = generatorName + " (" + str(rangeBegin) + "-" + str(rangeEnd) + ")[" + str(iterations) + "] Mean: " + \
            str(meanTestValue) + "; Var: " + str(varTestValue) + "; Period: " + str(periodTestValue) + "\n"
        statsFile.write(summary)
        statsFile.flush()
        statsFile.close()

build()

# for example: test("fibonacci", 1, "256 128 64 32 16", 5, 3, 256, 356, 100)
test("fibonacci", 1, "256 128 64 32 16", 5, 3, 256, 356, 2)
