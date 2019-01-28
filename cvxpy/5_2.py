import cvxpy as cvx
import numpy
import matplotlib.pyplot as plt

n = 100
m = 30
numpy.random.seed(1)
A = numpy.random.randn(n, m)
b = numpy.random.randn(n)
x = cvx.Variable(m)

constraints = [A * x == b]
obj = cvx.Minimize(cvx.pnorm(x, 1))
prob = cvx.Problem(obj, constraints)
result = prob.solve()

print("result : ", result)
