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
x = numpy.ones(n)
nu = numpy.zeros(p)

alpha = cvx.Parameter(value = 1e-2)
beta = cvx.Parameter(value = 5e-1)
tol = cvx.Parameter(value = 1e-7)
onse = numpy.ones(n)
vals = []
steps = []

while True:
    #evaluate residual
    r = numpy.concatenate((onse + cvx.log(x).value + A.T.dot(nu), A.dot(x) - b), axis = 0)
    #store residual norm
    vals.append(cvx.norm(r).value)
    #evalue hessian
    hess = cvx.diag(1.0 / x)
    #compute Newton step
    Pm = numpy.concatenate((numpy.concatenate((hess.value, A.T), axis = 1), numpy.concatenate((A, numpy.zeros((p, p))), axis = 1)), axis = 0)
    sol = numpy.linalg.solve(Pm, -r);
    x_step = sol[0 : n]
    nu_step = sol[n : n + p]
    #check for exit
    if cvx.norm(r).value <= tol.value:
        break
    #mulitple until bring to domain
    t = 1
    while min (x + t * x_step) <= 0: t = beta.value * t
    # compute t based on backtracking line search
    while cvx.norm(numpy.concatenate((onse + cvx.log(x + t * x_step).value + A.T.dot(nu + t * nu_step), A.dot(x + t * x_step) - b), axis = 0)).value > (1 - alpha.value * t) * cvx.norm(r).value:
        t = beta.value * t
    x = x + t * x_step
    nu = nu + t * nu_step
    steps.append(t)

#Plot process
#----------------------------------------#
fig,axes = plt.subplots(nrows = 1, ncols = 3)
axes[0].plot(list(range(len(vals))), vals, 'r--')
axes[0].set_xlabel('iter')
axes[0].set_ylabel('residual')
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
axes[2].set_ylabel('residual')
axes[2].set_title('infeasible start eq ctr')
#----------------------------------------#
fig.tight_layout()
plt.show()
#----------------------------------------#
