import cvxpy as cvx
import numpy
import matplotlib.pyplot as plt

x = cvx.Variable(2)

A = numpy.matrix([[1,  2],
                  [1, -4],
                  [5, 76]])
#b = numpy.matrix([[-2], [-3], [1]])
b = numpy.array([-2, -3, 1])

Q = numpy.matrix([[1, -0.5],
                  [-0.5, 2]])
f = numpy.matrix([[-1],[0]])
#f = numpy.array([-1,0])

constraints = [A*x <= b]

obj = cvx.Minimize(cvx.quad_form(x, Q) + f.T * x)

prob = cvx.Problem(obj, constraints)
result = prob.solve()

print("ctr 0 dual variable", constraints[0].dual_value)
print("result : ", result)
