import cvxpy as cvx
import numpy
import matplotlib.pyplot as plt

knot = 0.30
def import_data(fname):
    f = open(fname)
    data = numpy.array(f.read().split(',')).astype(float)
    f.close();
    return data;

def build_F(x):
    global knot
    F = numpy.zeros(shape = (len(x), 2))
    F = numpy.asmatrix(F)
    for i in range(len(x)):
        if x[i] < knot:
            F[i, 0] = 1
            F[i, 1] = 0
        elif x[i] > knot:
            F[i, 0] = 0
            F[i, 1] = 1
        else:
            F[i, 0] = 1
            F[i, 1] = 1
    return F

x = import_data('data_x')
y = import_data('data_y')
F = build_F(x)

#Build objective
alpha = cvx.Variable(2)
beta = cvx.Variable(2)
obj = cvx.Minimize(cvx.norm(cvx.diag(x) * F * alpha + F * beta - y))

#Build constraints
o = numpy.array([1, -1])
constraints = [o.T * alpha <= 0, knot * o.T * alpha + o.T * beta == 0]

prob = cvx.Problem(obj, constraints)
result = prob.solve()

print ("Alpha: \n", alpha.value)
print ("Beta: \n", beta.value)

plt.figure()
plt.plot(x,y,'r')

y_inter0 = alpha.value[0] * x + beta.value[0]
y_inter1 = alpha.value[1] * x + beta.value[1]

plt.plot(x,y_inter0, '-.g')
plt.plot(x,y_inter1, '--m')

plt.xlabel('x')
plt.ylabel('y')
plt.show()
