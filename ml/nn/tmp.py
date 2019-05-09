import numpy as np

a = np.array([1, 2, 3])

n = 3

m = np.zeros((3,3))

def S(i):
    np.exp(a[i])/np.sum(np.exp(a))

for i in range(0, 3):
    for j in range(0, 3):
        if i == j:
            m[i][j] = (np.exp(a[i])/np.sum(np.exp(a))) * (1 - (np.exp(a[i])/np.sum(np.exp(a))))
        else:
            m[i][j] = -1 * (np.exp(a[i])/np.sum(np.exp(a))) * (np.exp(a[i])/np.sum(np.exp(a)))

print (m)
print (a)

print (np.dot(a, m))
