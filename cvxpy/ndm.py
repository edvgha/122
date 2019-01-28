import cvxpy as cvx
import numpy
import matplotlib.pyplot as plt

n = 1000
m = 1000

numpy.random.seed(1)
A = numpy.random.randn(m, n)
x = numpy.zeros(n)

alpha = cvx.Parameter(value = 0.01)
beta = cvx.Parameter(value = 0.5)
tol = cvx.Parameter(value=1e-8)
vals = []
steps = []

while True:
    #evaluate function
    val = -cvx.sum(cvx.log(1 - A.dot(x))) - cvx.sum(cvx.log(1 + x)) - cvx.sum(cvx.log(1 - x))
    #store value
    vals.append(val.value)
    d = 1.0 / (1 - A.dot(x))
    #evalue grad
    grad = A.T.dot(d) - 1.0/(1 + x) + 1.0/(1 - x)
    #evalue hessian
    hess = A.T * cvx.diag(numpy.power(d, 2)) * A + cvx.diag(1.0/numpy.power(1 + x, 2) + 1.0/numpy.power(1 - x, 2))
    v = numpy.dot(-numpy.linalg.inv(hess.value), grad)
    #evalue lambda^2
    fprime = numpy.dot(grad.T, v)
    #check for exit
    if abs(fprime) / 2 <= tol.value:
        break
    #mulitple until x + t * del_x belongs to dom f
    t = 1
    while max(A.dot(x + t * v)) >= 1 or max(abs(x + t * v)) >= 1:
        t = beta.value * t
    # compute t based on backtracking line search
    while (-cvx.sum(cvx.log(1 - A.dot(x + t * v))) - cvx.sum(cvx.log(1 + (x + t * v))) - cvx.sum(cvx.log(1 - (x + t * v)))).value > val.value + alpha.value *  t * fprime:
        t = beta.value * t
    x = x + t * v
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
axes[2].set_title('Newton descent')
#----------------------------------------#
fig.tight_layout()
plt.show()
#----------------------------------------#
