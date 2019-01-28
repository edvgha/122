import cvxpy as cvx
import numpy as np
import matplotlib.pyplot as plt

n = 500
m = 100

# Generate initial data
np.random.seed(1)
A = np.random.randn(m, n)
x = np.random.uniform(0.1, 0.9, n)
#use b as A * x to make x feasible
b = A.dot(x)
c = np.random.uniform(0, 1, n)

# solves problem
# minimize c' * x - sum(log(x))
# subject to A * x = b
# using Newton's method, given strictly feasible starting point x_0
# input (A, b, c, x_0)
# returns primal and dual optimal points
# lambda_hist is a vector showing lambda^2/2 for each Newton step
def lp_acent(A, b, c, x):
    # check for full rank
    assert np.linalg.matrix_rank(A) == m
    # starting point should be from domain
    assert min(x) > 0
    # starting point should be feasible
    assert cvx.norm(A.dot(x) - b).value <= 1e-3

    # algorithm parameters
    alpha = cvx.Parameter(value = 0.01)
    beta = cvx.Parameter(value = 0.5)
    tol = cvx.Parameter(value=1e-6)
    # for stats
    lambda_hist = []
    vals = []
    # primal optimal
    x_star = -1
    # dual optimal
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
        # find Newton step by elimination method
        w = np.linalg.solve(np.dot(np.dot(A, h_inv), A.T), np.dot(np.dot(-A, h_inv), g))
        dx = np.dot(-h_inv, (np.dot(A.T, w) + g))
        # compute lambda descent
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
        while np.dot(c.T, (t * dx)) - cvx.sum(cvx.log(x + t * dx)).value + \
              cvx.sum(cvx.log(x)).value - alpha.value * t * v > 0:
            t = beta.value * t
        x = x + t * dx
    return x_star, nu_start, lambda_hist, vals

#verify KKT certificate
def KKT_cert_barrier(x_star, nu_start):
    # A.T * nu_start + grad_f == 0
    if np.max(np.dot(A.T, nu_start) + c) >= 1e-3:
        return False
    else:
        return True

def KKT_cert(x_star, nu_start, t):
    # A.T * nu_start + grad_f == 0
    if np.max(np.dot(A.T, nu_start) + t * c - 1.0/x_star) >= 1e-1:
        return False
    else:
        return True

def display(lambda_hist, vals):
    iters = len(lambda_hist) - 1
    fig,axes = plt.subplots(nrows = 1, ncols = 3)
    axes[0].plot(list(range(len(lambda_hist))[0:iters]), (lambda_hist)[0:iters], 'r--')
    axes[0].set_xlabel('iter')
    axes[0].set_ylabel('lambda_sqrt/2')
    axes[0].set_title('decrement')
    axes[1].plot(list(range(len(lambda_hist))[0:iters]), (cvx.log(lambda_hist).value)[0:iters], 'b+-')
    axes[1].set_xlabel('iter')
    axes[1].set_ylabel('lambda_sqrt/2')
    axes[1].set_title('log decrement')
    axes[2].plot(list(range(len(vals))[0:iters]), vals[0:iters], 'g*-')
    axes[2].set_xlabel('iter')
    axes[2].set_ylabel('f_values')
    axes[2].set_title('objective descent')

    fig.tight_layout()
    plt.show()

# standard form LP
# minimize c.T * x
# subject to A * x = b, x >= 0
# using barrier method, given strictly feasible x
# returns:
#   - primal optimal point x_star
#   - history, a 2 by k matrix that returns number of Newton steps
# in each centering step (top row) and duality gap (bottom row)
# (k is total number of centering steps)
#   - gap, optimal duality gap
# barrier method parameters
def lp_barrier(A, b, c, x_0):
    # barrier method parameters
    T_0 = 1
    MU = 20
    # duality gap stopping criterion
    EPSILON = 1e-3
    t = T_0
    x_i = x_0
    nu_i = 0
    history = []
    while True:
        x_star, nu_star, lambda_hist, vals = lp_acent(A, b, t * c, x_i)
        x_i = x_star
        nu_i = nu_star
        gap = n / t
        history.append([len(lambda_hist), gap])
        if gap < EPSILON: break
        t = MU * t
    assert KKT_cert(x_i, nu_i, t)
    return x_i, history

def main():
    x_star, history = lp_barrier(A, b, c, x)
    x_list = []
    y_list = []
    acc = 0
    print (len(history))
    for i in range(len(history)):
        y_list.append(history[i][1])
        y_list.append(history[i][1])
        x_list.append(acc + history[i - 1][0])
        acc = acc + history[i - 1][0]
        x_list.append(acc + history[i][0])
    plt.step(x_list, y_list)
    plt.show()

if __name__ == '__main__' : main()
