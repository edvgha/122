import numpy as np
import torch
import torch.nn as nn
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d

import os
os.environ['KMP_DUPLICATE_LIB_OK']='True'

INPUT_SIZE = 1
OUTPUT_SIZE = 1
HID_SIZE = 16


class Target(nn.Module):
    def __init__(self, in_size, out_size):
        super(Target, self).__init__()

        self.mu = nn.Sequential(
            nn.Linear(in_size, out_size),
            # nn.Tanh(),
            # nn.Linear(HID_SIZE, HID_SIZE),
            # nn.Tanh(),
            # nn.Linear(HID_SIZE, out_size),
            # nn.Tanh(),
        )

    def forward(self, x):
        return self.mu(x)

class Network(nn.Module):
    def __init__(self, in_size, out_size):
        super(Network, self).__init__()

        self.mu = nn.Sequential(
            nn.Linear(in_size, out_size),
            # nn.Tanh(),
            # nn.Linear(HID_SIZE, HID_SIZE),
            # nn.Tanh(),
            # nn.Linear(HID_SIZE, out_size),
            # nn.Tanh(),
        )

    def forward(self, x):
        return self.mu(x)

def Inputs(batch_size):
    return torch.rand((batch_size, INPUT_SIZE))

def Input_Output_Net(batch_size):
    # generate input
    input = Inputs(batch_size)
    # get target network
    target = torch.jit.script(Target(INPUT_SIZE, OUTPUT_SIZE))
    output = target(input)
    return input, output, target

def Show2d(input, output1, output2):
    X = input.squeeze().detach().numpy()
    Y1 = output1.squeeze().detach().numpy()
    Y2 = output2.squeeze().detach().numpy()

    fix, ax = plt.subplots()
    ax.scatter(X, Y1, label='target')
    ax.scatter(X, Y2, label='net')
    ax.legend()
    ax.grid()
    plt.show()

def Show3D(input, output):
    # Input shape Nx1, inputs are in (x, y) plane
    # Output shpae Nx1, output is a z axis
    # Plot X,Y,Z
    X = input.detach().numpy()[:, 0]
    Y = input.detach().numpy()[:, 1]
    Z = output.squeeze().detach().numpy()
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot_trisurf(X, Y, Z, color='white', edgecolors='grey', alpha=0.5)
    ax.scatter(X, Y, Z, c='red')
    plt.show()

if __name__ == "__main__":
    input, output, target = Input_Output_Net(1024)
    network = torch.jit.script(Network(INPUT_SIZE, OUTPUT_SIZE))
    Show2d(input, output, network(input))
