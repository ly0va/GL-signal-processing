#!/usr/bin/python3

import sys
import numpy as np
import matplotlib.pyplot as plt

if len(sys.argv) < 3:
    print("USAGE: ./graph.py FILENAME SAMPLE_RATE")
    exit(0)

filename = sys.argv[1]
fs = float(sys.argv[2])

y = [float(x) for x in open(filename).readlines()]
x = np.arange(0, len(y)/fs, 1/fs)
y = y[:len(x)]

plt.plot(x, y)
plt.xlabel('x')
plt.ylabel('y')
plt.title('Signal')
plt.show()

