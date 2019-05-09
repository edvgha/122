"""Computation graph node types

Nodes must implement the following methods:
__init__   - initialize node
forward    - (step 1 of backprop) retrieve output ("out") of predecessor nodes (if
             applicable), update own output ("out"), and set gradient ("d_out") to zero
backward   - (step 2 of backprop), assumes that forward pass has run before.
             Also assumes that backward has been called on all of the node's
             successor nodes, so that self.d_out contains the
             gradient of the graph output with respect to the node output.
             Backward computes summands of the derivative of graph output with
             respect to the inputs of the node, corresponding to paths through the graph
             that go from the node's input through the node to the graph's output.
             These summands are added to the input node's d_out array.
get_predecessors - return a list of the node's parents

Nodes must furthermore have a the following attributes:
node_name  - node's name (a string)
out      - node's output
d_out    - derivative of graph output w.r.t. node output

This computation graph framework was designed and implemented by
Philipp Meerkamp, Pierre Garapon, and David Rosenberg.
License: Creative Commons Attribution 4.0 International License
"""

import numpy as np

class ValueNode(object):
    """Computation graph node having no input but simply holding a value"""
    def __init__(self, node_name):
        self.node_name = node_name
        self.out = None
        self.d_out = None

    def forward(self):
        self.d_out = np.zeros(self.out.shape)
        return self.out

    def backward(self):
        pass

    def get_predecessors(self):
        return []

class VectorScalarAffineNode(object):
    """ Node computing an affine function mapping a vector to a scalar."""
    def __init__(self, x, w, b, node_name):
        """
        Parameters:
        x: node for which x.out is a 1D numpy array
        w: node for which w.out is a 1D numpy array of same size as x.out
        b: node for which b.out is a numpy scalar (i.e. 0dim array)
        node_name: node's name (a string)
        """
        self.node_name = node_name
        self.out = None
        self.d_out = None
        self.x = x
        self.w = w
        self.b = b

    def forward(self):
        self.out = np.dot(self.x.out, self.w.out) + self.b.out
        self.d_out = np.zeros(self.out.shape)
        return self.out

    def backward(self):
        d_x = self.d_out * self.w.out
        d_w = self.d_out * self.x.out
        d_b = self.d_out
        self.x.d_out += d_x
        self.w.d_out += d_w
        self.b.d_out += d_b

    def get_predecessors(self):
        return [self.x, self.w, self.b]

class SquaredL2DistanceNode(object):
    """ Node computing L2 distance (sum of square differences) between 2 arrays."""
    def __init__(self, a, b, node_name):
        """
        Parameters:
        a: node for which a.out is a numpy array
        b: node for which b.out is a numpy array of same shape as a.out
        node_name: node's name (a string)
        """
        self.node_name = node_name
        self.out = None
        self.d_out = None
        self.a = a
        self.b = b
        # Variable for caching values between forward and backward
        self.a_minus_b = None

    def forward(self):
        self.a_minus_b = self.a.out - self.b.out
        self.out = np.sum(self.a_minus_b ** 2)
        self.d_out = np.zeros(self.out.shape)
        return self.out

    def backward(self):
        d_a = self.d_out * 2 * self.a_minus_b
        d_b = -self.d_out * 2 * self.a_minus_b
        self.a.d_out += d_a
        self.b.d_out += d_b.reshape(self.b.d_out.shape)
        return self.d_out

    def get_predecessors(self):
        return [self.a, self.b]

class L2NormPenaltyNode(object):
    """ Node computing l2_reg * ||w||^2 for scalars l2_reg and vector w"""
    def __init__(self, l2_reg, w, node_name):
        """
        Parameters:
        l2_reg: a scalar value >=0 (not a node)
        w: a node for which w.out is a numpy vector
        node_name: node's name (a string)
        """
        self.node_name = node_name
        self.out = None
        self.d_out = None
        self.l2_reg = np.array(l2_reg)
        self.w = w

    def forward(self):
        self.out = self.l2_reg * np.dot(self.w.out, self.w.out)
        self.d_out = np.zeros(self.out.shape)
        return self.out

    def backward(self):
        self.w.d_out += 2 * self.l2_reg * self.w.out * self.d_out
        return self.d_out

    def get_predecessors(self):
        return [self.w]

class SumNode(object):
    """ Node computing a + b, for numpy arrays a and b"""
    def __init__(self, a, b, node_name):
        """
        Parameters:
        a: node for which a.out is a numpy array
        b: node for which b.out is a numpy array of the same shape as a
        node_name: node's name (a string)
        """
        self.node_name = node_name
        self.a = a
        self.b = b
        self.out = None
        self.d_out = None

    def forward(self):
        self.out = self.a.out + self.b.out
        self.d_out = np.zeros(self.out.shape)
        return self.out

    def backward(self):
        self.a.d_out += self.d_out
        self.b.d_out += self.d_out
        return self.d_out

    def get_predecessors(self):
        return [self.a, self.b]

class AffineNode(object):
    """Node implementing affine transformation (W,x,b)-->Wx+b, where W is a matrix,
    and x and b are vectors
        Parameters:
        W: node for which W.out is a numpy array of shape (m,d)
        x: node for which x.out is a numpy array of shape (d)
        b: node for which b.out is a numpy array of shape (m) (i.e. vector of length m)
    """
    def __init__(self, x, W, b, node_name):
        """
        Parameters:
        x: node for which x.out is a 1D numpy array
        w: node for which W.out is a 2D numpy array
        b: node for which b.out is a 1D numpy array
        node_name: node's name (a string)
        """
        self.node_name = node_name
        self.out = None
        self.d_out = None
        self.x = x
        self.W = W
        self.b = b

    def forward(self):
        self.out = np.dot(self.W.out, self.x.out) + self.b.out
        self.d_out = np.zeros(self.out.shape)
        return self.out

    def backward(self):
        # W.T -> dxm
        # d_out -> mx1
        # d_x -> dx1
        d_x = np.dot(self.W.out.T, self.d_out)
        # d_out -> mx1
        # x.out.T -> 1xd
        #d_W = np.dot(np.array([self.d_out]), np.array([self.x.out]))
        d_W = np.dot(np.array([self.d_out]).T, np.array([self.x.out]))
        # d_out -> mx1
        # d_b = -> mx1
        d_b = self.d_out
        self.x.d_out += d_x
        self.W.d_out += d_W
        self.b.d_out += d_b

    def get_predecessors(self):
        return [self.x, self.W, self.b]

class TanhNode(object):
    """Node tanh(a), where tanh is applied elementwise to the array a
        Parameters:
        a: node for which a.out is a numpy array
    """
    def __init__(self, a, node_name):
        """
        Parameters:
        x: node for which x.out is a  1D array
        node_name: node's name (a string)
        """
        self.node_name = node_name
        self.out = None
        self.d_out = None
        self.a = a

    def forward(self):
        self.out = np.tanh(self.a.out)
        self.d_out = np.zeros(self.out.shape)
        return self.out

    def backward(self):
        self.a.d_out += self.d_out * (1 - (self.out * self.out))

    def get_predecessors(self):
        return [self.a]

class SoftMax(object):
    """Node softmax(a), where i-th element is exp(a[i])/sum_all_elements(exp(a[j]))
        Parameters:
        a: node for which a.out is a numpy array
    """
    def __init__(self, a, node_name):
        """
        Parameters:
        a: node for which a.out is a  1D array
        node_name: node's name (a string)
        """
        self.node_name = node_name
        self.out = None
        self.d_out = None
        self.a = a

    def forward(self):
        self.s = np.sum(np.exp(self.a.out))
        self.out = np.exp(self.a.out) / self.s
        self.d_out = np.zeros(self.out.shape)
        return self.out

    def backward(self):
        """
            |D1S1 ... DNS1|
            | .        .  |
        DS =| .        .  |
            | .        .  |
            |D1SN ... DNSN|

        DjSi = Si(Delta(i,j) - Sj)

        Si = exp(a[i])/sum(exp(a))
        """

        m = np.zeros((self.out.shape, self.out.shape))
        for i in range(0, self.out.shape):
            for j in range(0, self.out.shape):
                if i == j:
                    m[i][j] = (np.exp(a[i])/np.sum(np.exp(a))) * (1 - (np.exp(a[i])/np.sum(np.exp(a))))
                else:
                    m[i][j] = -1 * (np.exp(a[i])/np.sum(np.exp(a))) * (np.exp(a[i])/np.sum(np.exp(a)))
        self.a.d_out += np.dot(self.d_out, m)


    def get_predecessors(self):
        return [self.a]

