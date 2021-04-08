from   num2dac import num2dac
from   DAC     import *
import numpy as np
import time
from math import sin, pi
import matplotlib
import matplotlib.pyplot as plt


def CreateSine(frequency, time, samplingFrequency):
    omega = 2 * pi * frequency
    times = [0] * (samplingFrequency * time + 1)
    for i in range(1, len(times)):
        times[i] = times[i-1] + (1 / samplingFrequency)
    values = times.copy()
    for i in range(len(values)):
        values[i] = sin(times[i] * omega)
    print(values)
    plt.grid()
    plt.scatter(times, values)
    plt.show()
    

def main():
    frequency = int(input())
    time      = int(input())
    CreateSine(frequency, time, 100)

main()