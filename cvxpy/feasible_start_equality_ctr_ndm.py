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
x = x_hat

alpha = cvx.Parameter(value = 1e-2)
beta = cvx.Parameter(value = 5e-1)
tol = cvx.Parameter(value = 1e-7)
onse = numpy.ones(n)
vals = []
steps = []

while True:
    #evaluate function
    val = cvx.sum(x.T * cvx.log(x))
    #store value
    vals.append(val.value)
    #evalue grad
    grad = cvx.log(x) + onse
    #evalue hessian
    hess = cvx.diag(1.0 / x)
    #compute Newton step
    Pm = numpy.concatenate((numpy.concatenate((hess.value, A.T), axis = 1), numpy.concatenate((A, numpy.zeros((p, p))), axis = 1)), axis = 0)
    Pa = numpy.concatenate((-grad.value, numpy.zeros(p)), axis = 0)
    N_step = (numpy.linalg.solve(Pm, Pa))[0 : n]
    #evalue lambda^2
    fprime = numpy.dot(grad.T.value, N_step)
    #check for exit
    if abs(fprime) <= tol.value:
        break
    #mulitple until bring to domain
    t = 1
    while min (x + t * N_step) <= 0: t = beta.value * t
    # compute t based on backtracking line search
    while ((x + t * N_step).T * cvx.log(x + t * N_step)).value >= val.value + t * alpha.value * fprime:
        t = beta.value * t
    x = x + t * N_step
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
axes[2].set_title('feasible start eq ctr')
#----------------------------------------#
fig.tight_layout()
plt.show()
#----------------------------------------#
