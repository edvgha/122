import cvxpy as cvx
import numpy
import matplotlib.pyplot as plt

M = 20
N = 20

X = numpy.matrix([[3.5674, 4.1253, 2.8535, 5.1892, 4.3273, 3.8133, 3.4117,
                   3.8636, 5.0668, 3.9044, 4.2944, 4.7143, 3.3082, 5.2540,
                   2.5590, 3.6001, 4.8156, 5.2902, 5.1908, 3.9802],
                 [-2.9981, 0.5178, 2.1436, -0.0677, 0.3144, 1.3064, 3.9297,
                  0.2051, 0.1067, -1.4982, -2.4051, 2.9224, 1.5444, -2.8687,
                  1.0281, 1.2420, 1.2814, 1.2035, -2.1644, -0.2821]]);

Y = numpy.matrix([[-4.5665, -3.6904, -3.2881, -1.6491, -5.4731, -3.6170, -1.1876,
                   -1.0539, -1.3915, -2.0312, -1.9999, -0.2480, -1.3149, -0.8305,
                   -1.9355, -1.0898, -2.6040, -4.3602, -1.8105, 0.3096],
                 [2.4117, 4.2642, 2.8460, 0.5250, 1.9053, 2.9831, 4.7079,
                  0.9702, 0.3854, 1.9228, 1.4914, -0.9984, 3.4330, 2.9246,
                  3.0833, 1.5910, 1.5266, 1.6256, 2.5037, 1.4384]]);

a = cvx.Variable(2)
b = cvx.Variable(1)

constraints = [a.T * X - b >= 1, a.T * Y - b <= -1]

prob = cvx.Problem(cvx.Maximize(0), constraints)
prob.solve()

a1 = cvx.Variable(2)
b1 = cvx.Variable(1)
q = cvx.Variable(1)
constraints1 = [a1.T * X - b1 >= q, a1.T * Y - b1 <= -q, cvx.norm(a1) <= 1]
prob1 = cvx.Problem(cvx.Maximize(q), constraints1)
prob1.solve()
print (a1.value)
print (b1.value)

#A = numpy.matrix([a1.value - a2.value,a1.value - a3.value])
#b = numpy.array([b1.value - b2.value, b1.value - b3.value])
#p = numpy.linalg.solve(A, b)

# PLOT
x0 = numpy.array(X[0])
x1 = numpy.array(X[1])
y0 = numpy.array(Y[0])
y1 = numpy.array(Y[1])

fig,axes = plt.subplots(nrows = 1, ncols = 1)
axes.scatter(x0, x1, marker = '*')
axes.scatter(y0, y1, marker = '+')
t = numpy.arange(-6,9,3);
line1 = (-t * a[1].value + b.value) / a[0].value
line2 = (-t * a1[1].value + b1.value) / a1[0].value
axes.plot(line1, t, ls = '--')
axes.plot(line2, t, ls = '-.')

fig.tight_layout()
plt.show()
