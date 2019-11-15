import numpy as np

def foo():
    return 1, 2

a, b = foo()

print (a, b)

for i in np.arange(1, 10 + 1):
    print (i)

l = [(0.3, 0, 0.0, False), (0.3, 0, 0.0, False), (0.3, 4, 0.0, False)]

for (p, n, r, t) in l:
    print (p, n, r, t)
