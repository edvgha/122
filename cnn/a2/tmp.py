import numpy as np

num_inputs = 2
input_shape = (4, 5, 6)
output_dim = 3

input_size = num_inputs * np.prod(input_shape)
weight_size = output_dim * np.prod(input_shape)

x = np.linspace(-0.1, 0.5, num=input_size).reshape(num_inputs, *input_shape)

s = int(np.prod(x.shape) / (x.shape)[0])

print (s)
x = x.reshape([2, s])

print (x)

print (1.0/2e-5)
