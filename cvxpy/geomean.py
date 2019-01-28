import cvxpy as cvx
import numpy
import matplotlib.pyplot as plt

#minimize sum log -> maximize geomean

n = 5
m = 10

x = cvx.Variable(n)
P = numpy.matrix([[3.5000, 1.1100, 1.1100, 1.0400, 1.0100],
                  [0.5000, 0.9700, 0.9800, 1.0500, 1.0100],
                  [0.5000, 0.9900, 0.9900, 0.9900, 1.0100],
                  [0.5000, 1.0500, 1.0600, 0.9900, 1.0100],
                  [0.5000, 1.1600, 0.9900, 1.0700, 1.0100],
                  [0.5000, 0.9900, 0.9900, 1.0600, 1.0100],
                  [0.5000, 0.9200, 1.0800, 0.9900, 1.0100],
                  [0.5000, 1.1300, 1.1000, 0.9900, 1.0100],
                  [0.5000, 0.9300, 0.9500, 1.0400, 1.0100],
                  [3.5000, 0.9900, 0.9700, 0.9800, 1.0100]])

constraints = [cvx.sum(x) == 1, x >= 0]
obj = cvx.Maximize(cvx.geo_mean(P * x))

prob = cvx.Problem(obj, constraints)
result = prob.solve()

print("result : ", result)
print (x.value)
