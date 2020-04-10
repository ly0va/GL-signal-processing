#!/usr/bin/python3

import sys
import numpy as np
import matplotlib.pyplot as plt

filename = sys.argv[1]
fs = float(sys.argv[2])

y = [int(x) for x in open(filename).readlines()]
x = np.arange(0, (len(y)-1)/fs, 1/fs)

plt.plot(x, y)
plt.xlabel('x')
plt.ylabel('y')
plt.title('Signal')
plt.show()

