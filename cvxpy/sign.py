import cvxpy as cvx
import numpy

x = cvx.Variable()
a = cvx.Parameter(nonpos=True)
c = numpy.array([1, -1])

print("sign of x:", x.sign)
print("sign of a:", a.sign)
print("sign of square(x):", cvx.square(x).sign)
print("sign of c*a:", (c*a).sign)
