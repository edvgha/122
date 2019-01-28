import cvxpy as cvx
import numpy

A = numpy.matrix([[1, 2, 0, 1],
                 [0, 0, 3, 1],
                 [0, 3, 1, 1],
                 [2, 1, 2, 5],
                 [1, 0, 3, 2]])
A = numpy.asmatrix(A)

cmax = numpy.array([100, 100, 100, 100, 100])

pdisc = numpy.array([2, 1, 4, 2])
p = numpy.array([3, 2, 7, 6])
q = numpy.array([4, 10, 5, 10])

x = cvx.Variable(4)
u = cvx.Variable(4)

# Ceate two constraints.
constraints = [A * x <= cmax, x >= 0, p * x >= u, (p * q + pdisc * (x - q)) >= u]
obj = cvx.Maximize(cvx.sum(u))

#constraints = [A * x <= cmax, x >= 0]
#obj = cvx.Maximize(cvx.sum(cvx.minimum(p*x, p*q + pdisc*(x - q))))

prob = cvx.Problem(obj, constraints)
prob.solve()  # Returns the optimal value.
print("status:", prob.status)
print("optimal value", prob.value)
print("optimal var", x.value)
