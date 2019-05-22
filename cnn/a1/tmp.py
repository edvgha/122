import numpy as np


A = np.array([[1, 2, 3], [4, 5,6 ], [7, 8, 9]])
b = np.array([1, 1, 1])
c = A - b


x = np.array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]])
y = np.array([[1, 1, 1, 1], [2, 2, 2, 2]])

z = np.subtract(x, y.T)

print (z)
