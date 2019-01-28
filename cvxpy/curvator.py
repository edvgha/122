import cvxpy as cvx
import numpy

x = cvx.Variable()
a = cvx.Parameter(nonneg=True)

print("curvature of x:", x.curvature)
print("curvature of a:", a.curvature)
print("curvature of square(x):", cvx.square(x).curvature)
print("curvature of sqrt(x):", cvx.sqrt(x).curvature)
