import cvxpy as cvx
import numpy
import matplotlib.pyplot as plt

M = 20
N = 20
P = 20

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

Z = numpy.matrix([[1.7451, 2.6345, 0.5937, -2.8217, 3.0304, 1.0917, -1.7793,
                   1.2422, 2.1873, -2.3008, -3.3258, 2.7617, 0.9166, 0.0601,
                   -2.6520, -3.3205, 4.1229, -3.4085, -3.1594, -0.7311],
                 [-3.2010, -4.9921, -3.7621, -4.7420, -4.1315, -3.9120, -4.5596,
                  -4.9499, -3.4310, -4.2656, -6.2023, -4.5186, -3.7659, -5.0039,
                  -4.3744, -5.0559, -3.9443, -4.0412, -5.3493, -3.0465]])

a1 = cvx.Variable(2)
a2 = cvx.Variable(2)
a3 = cvx.Variable(2)
b1 = cvx.Variable(1)
b2 = cvx.Variable(1)
b3 = cvx.Variable(1)

constraints = [a1.T * X - b1 >= a2.T * X - b2 + 1,
               a1.T * X - b1 >= a3.T * X - b3 + 1,
               a2.T * Y - b2 >= a1.T * Y - b1 + 1,
               a2.T * Y - b2 >= a3.T * Y - b3 + 1,
               a3.T * Z - b3 >= a1.T * Z - b1 + 1,
               a3.T * Z - b3 >= a2.T * Z - b2 + 1,
               a1 + a2 + a3 == 0,
               b1 + b2 + b3 == 0]

prob = cvx.Problem(cvx.Maximize(0), constraints)
prob.solve()

#A = numpy.matrix([a1.value - a2.value,a1.value - a3.value])
#b = numpy.array([b1.value - b2.value, b1.value - b3.value])
#p = numpy.linalg.solve(A, b)

# PLOT
x0 = numpy.array(X[0])
x1 = numpy.array(X[1])
y0 = numpy.array(Y[0])
y1 = numpy.array(Y[1])
z0 = numpy.array(Z[0])
z1 = numpy.array(Z[1])

fig,axes = plt.subplots(nrows = 1, ncols = 1)
axes.scatter(x0, x1, marker = '*')
axes.scatter(y0, y1, marker = 's')
axes.scatter(z0, z1, marker = '+')
t = numpy.arange(-7,7,1);
line1 = (-t * a1[0].value + b1.value) / a1[1].value
line2 = (-t * a2[0].value + b2.value) / a2[1].value
line3 = (-t * a3[0].value + b3.value) / a3[1].value
axes.plot(t, line1, ls = '--')
axes.plot(t, line2, ls = '-')
axes.plot(t, line3, ls = '-.')

fig.tight_layout()
plt.show()
