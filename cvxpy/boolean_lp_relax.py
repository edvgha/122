from cvxpy import *
import numpy as np

np.random.seed(0)

(m, n) = (300, 100)

A = np.random.rand(m, n); A = np.asmatrix(A)
b = A.dot(np.ones((n, 1)))/2; b = np.asarray(b)
b = np.reshape(b, (np.product(b.shape),))
c = - np.random.rand(n, 1); c = np.asmatrix(c)

x = Variable(n, 1)

constraints = [A*x <= b, x >= 0, x <= 1]
obj = Minimize(c.T * x)

prob = Problem(obj, constraints)
result = prob.solve()

print("result : ", result)
print (x.value)
