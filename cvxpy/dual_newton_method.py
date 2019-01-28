import cvxpy as cvx
import numpy
import matplotlib.pyplot as plt

n = 100
p = 30

numpy.random.seed(1)
A = numpy.random.randn(p, n)
assert numpy.linalg.matrix_rank(A) == p
x_hat = numpy.random.uniform(0.1, 0.9, n)
b = A.dot(x_hat)
nu = numpy.zeros(p)

alpha = cvx.Parameter(value = 1e-2)
beta = cvx.Parameter(value = 5e-1)
tol = cvx.Parameter(value = 1e-7)
ones = numpy.ones(n)
vals = []
steps = []

while True:
    #evaluate function
    val = numpy.dot(b.T, nu) + cvx.sum(numpy.exp(-A.T.dot(nu) - ones)).value
    #store value
    vals.append(val)
    #evalue grad
    grad = b - A.dot(numpy.exp(-A.T.dot(nu) - ones))
    #evalue hessian
    hess = (A.dot(cvx.diag(numpy.exp(-A.T.dot(nu) - ones)).value)).dot(A.T)
    #compute Newton step
    v = numpy.linalg.solve(-hess, grad)
    #evalue lambda^2
    fprime = numpy.dot(grad.T, v)
    #check for exit
    if abs(fprime) <= tol.value:
        break
    t = 1
    # compute t based on backtracking line search
    while (numpy.dot(b.T, (nu + t * v)) + cvx.sum(numpy.exp(-A.T.dot(nu + t * v) - ones)).value) > val + t * alpha.value * fprime :
        t = beta.value * t
    nu = nu + t * v
    steps.append(t)

#Plot process
#----------------------------------------#
fig,axes = plt.subplots(nrows = 1, ncols = 3)
axes[0].plot(list(range(len(vals))), vals, 'r--')
axes[0].set_xlabel('iter')
axes[0].set_ylabel('fvalue')
axes[0].set_title('descent')
#----------------------------------------#
axes[1].plot(list(range(len(steps))), steps, 'g*-')
axes[1].set_xlabel('iter')
axes[1].set_ylabel('step')
axes[1].set_title('BLS')
#----------------------------------------#
l = vals[len(vals) - 1]
relative = list(map(lambda e: e - l, vals))
axes[2].plot(list(range(len(relative))), relative, 'b+-')
axes[2].set_xlabel('iter')
axes[2].set_ylabel('f(x) - p')
axes[2].set_title('dual newton method')
#----------------------------------------#
fig.tight_layout()
plt.show()
#----------------------------------------#
