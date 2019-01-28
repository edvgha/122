import matplotlib
import matplotlib.pyplot as plt
import numpy as np

#x = np.linspace(0, 5, 10)
#y = x ** 2
#plt.figure()
#plt.plot(x, y, 'r')
#plt.xlabel('x')
#plt.ylabel('y')
#plt.title('title')

x1 = [1, 2, 3, 4, 5, 6, 7]
y1 = [1, 2, 3, 4, 5, 6, 7]

x2 = [2, 4, 6, 8, 10, 12, 14, 16]
y2 = [1, 2, 3, 4, 5, 6, 7, 8]

#----------------------------------------#
fig,axes = plt.subplots(nrows = 1, ncols = 2)
axes[0].plot(x1, y1, 'r')
axes[0].set_xlabel('fvalue')
axes[0].set_ylabel('iter')
axes[0].set_title('descent')
#----------------------------------------#
axes[1].plot(x2, y2, 'g')
axes[1].set_xlabel('step')
axes[1].set_ylabel('iter')
axes[1].set_title('BLS')
#----------------------------------------#
fig.tight_layout()
plt.show()
#----------------------------------------#

