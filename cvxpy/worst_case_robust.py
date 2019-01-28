import cvxpy as cvx
import numpy
import matplotlib.pyplot as plt

A_bar = numpy.matrix([[60, 45, -8],
                      [90, 30, -30],
                      [0,  -8, -4],
                      [30, 10, -10]])

R = numpy.matrix([[0.05, 0.05, 0.05],
                  [0.05, 0.05, 0.05],
                  [0.05, 0.05, 0.05],
                  [0.05, 0.05, 0.05]])

b = numpy.array([-6, -3, 18, -9])

x = cvx.Variable(3)
y = cvx.Variable(4)
z = cvx.Variable(3)

constraints = [A_bar * x + R * z - b - y <= 0, -A_bar * x + R * z + b - y <= 0, x <= z, x >= -z]

objective = cvx.Minimize(cvx.norm(y))

problem = cvx.Problem(objective, constraints)
result = problem.solve()

print ("result: %f \n" % result)
print ("x: \n" , x.value)
