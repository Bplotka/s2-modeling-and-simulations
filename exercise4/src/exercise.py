import matplotlib.pyplot as plot
import numpy as np
import sys

M = 1.0
L = 1.0


class Euler(object):
    def __init__(self, x, acc):
        self.x = x
        self.acc = acc

    def func(self, x, y):
        return np.cos(x*y*1000)

    def truncation_error(self, step):
        return step*M/(2*L) * (np.e ** L - 1)

    def get_step(self, step, acc):
        return step if self.truncation_error(step) < acc else self.get_step(step/2, acc)

    def get_points(self):
        pointsX = [0]
        pointsY = [self.x]
        step = self.get_step(1.0,  self.acc)
        print "Step: " + str(step)

        for pointX in np.arange(step, 1, step):
            self.x = self.x + step * self.func(self.x, pointX)
            pointsX.append(pointX)
            pointsY.append(self.x)

        return (pointsX, pointsY)


def main():
    euler = Euler(float(sys.argv[1]), float(sys.argv[2]))
    pointsX = []
    pointsY = []

    pointsX, pointsY = euler.get_points()

    plot.plot(pointsX, pointsY)
    plot.show()

if __name__ == "__main__":
    main()
