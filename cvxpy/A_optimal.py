import cvxpy as cvx
import cv2
import numpy as np
from matplotlib import pyplot as plt
from scipy.linalg import *

n = 5
p = 20
m = 30
V = np.random.randn(n, p)

lam = cvx.Variable(p)

obj = 0
for k in range(n):
    ek = np.zeros(n,)
    ek[k] = 1
    obj = obj + (1/m) * cvx.matrix_frac(ek, V * cvx.diag(lam) * V.T)

prob = cvx.Problem(cvx.Minimize(obj), [cvx.sum(lam) == 1, lam >= 0])
lower_bound = prob.solve()

print ('lower_bound:\n', lower_bound)

#round up
m_rnd = np.around(m * lam.value)
print ('sum : ', np.sum(m_rnd), '\n')
