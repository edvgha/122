import numpy as np

for _ in range(10):
    print('a')

print(np.reciprocal(5.))

x = np.zeros([2, 3])
x[0,0] = 1
x[1,1] = 2
x[0, 2] = 3
print(x)
print(np.argmax(x[:, 1], axis=0))
print("_----------------_")
print(np.random.randint(0,10))
print(np.random.randint(0,10))
print(np.random.randint(0,10))