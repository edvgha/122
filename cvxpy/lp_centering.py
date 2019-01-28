import cvxpy as cvx
import numpy as np
import matplotlib.pyplot as plt

n = 500
m = 100

np.random.seed(1)
A = np.random.randn(m, n)
x = np.random.uniform(0.1, 0.9, n)
#use b as A * x to make x feasible
b = A.dot(x)
c = np.random.uniform(0, 1, n)

assert np.linalg.matrix_rank(A) == m
assert min(x) > 0
assert cvx.norm(A.dot(x) - b).value <= 1e-3

alpha = cvx.Parameter(value = 0.01)
beta = cvx.Parameter(value = 0.5)
tol = cvx.Parameter(value=1e-6)
lambda_hist = []
vals = []
x_star = -1
nu_start = -1

while True:
    #evaluate function
    val = np.dot(c.T, x) - cvx.sum(cvx.log(x)).value
    vals.append(val)
    #evalue grad
    g = c - 1.0/x
    #evalue hessian
    h_inv = cvx.diag(x * x).value
    # Newton step via whole KKT system
    # M = [H A.T, A zeros(m,m)]
    # d = solve (M, [-g; zeros(m,1)]
    # dx = d[1:n]
    # w = d[n + 1: n + m]
    # fine Newton step by elimination method
    w = np.linalg.solve(np.dot(np.dot(A, h_inv), A.T), np.dot(np.dot(-A, h_inv), g))
    dx = np.dot(-h_inv, (np.dot(A.T, w) + g))

    lambdasqr = np.dot(-dx.T, g)
    lambda_hist.append(lambdasqr / 2)
    if lambdasqr / 2 <= tol.value: break
    else: x_star = x; nu_start = w

    #backtracking line search
    #first bring the point inside the domain
    t = 1
    while min(x + t * dx) <= 0: t = beta.value * t
    #do backtracking line search
    v = np.dot(g.T, dx)
    while np.dot(c.T, (t * dx)) - cvx.sum(cvx.log(x + t * dx)).value + cvx.sum(cvx.log(x)).value - alpha.value * t * v > 0:
        t = beta.value * t
    x = x + t * dx

### Check KKT condition A.T * nu_start + grad_f == 0 (with some tolerance value)
if np.max(np.dot(A.T, nu_start) + c - 1.0/x_star) >= 1e-2:
    print (np.max(np.dot(A.T, nu_start) + c - 1.0/x_star))
    print ("KKT CONDITION FAILED")
else:
    print ("KKT CONDITION PASS")
#Plot process
#----------------------------------------#
iters = len(lambda_hist)
fig,axes = plt.subplots(nrows = 1, ncols = 3)
axes[0].plot(list(range(len(lambda_hist))[0:iters]), (lambda_hist)[0:iters], 'r--')
axes[0].set_xlabel('iter')
axes[0].set_ylabel('lambda_sqrt/2')
axes[0].set_title('decrement')
#----------------------------------------#
axes[1].plot(list(range(len(lambda_hist))[0:iters]), (cvx.log(lambda_hist).value)[0:iters], 'b+-')
axes[1].set_xlabel('iter')
axes[1].set_ylabel('lambda_sqrt/2')
axes[1].set_title('log decrement')
#----------------------------------------#
axes[2].plot(list(range(len(vals))[0:iters]), vals[0:iters], 'g*-')
axes[2].set_xlabel('iter')
axes[2].set_ylabel('f_values')
axes[2].set_title('objective descent')
#----------------------------------------#
fig.tight_layout()
plt.show()
#----------------------------------------#
