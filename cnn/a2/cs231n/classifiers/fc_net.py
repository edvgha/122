from builtins import range
from builtins import object
import numpy as np

from cs231n.layers import *
from cs231n.layer_utils import *


class TwoLayerNet(object):
    """
    A two-layer fully-connected neural network with ReLU nonlinearity and
    softmax loss that uses a modular layer design. We assume an input dimension
    of D, a hidden dimension of H, and perform classification over C classes.

    The architecure should be affine - relu - affine - softmax.

    Note that this class does not implement gradient descent; instead, it
    will interact with a separate Solver object that is responsible for running
    optimization.

    The learnable parameters of the model are stored in the dictionary
    self.params that maps parameter names to numpy arrays.
    """

    def __init__(self, input_dim=3*32*32, hidden_dim=100, num_classes=10,
                 weight_scale=1e-3, reg=0.0):
        """
        Initialize a new network.

        Inputs:
        - input_dim: An integer giving the size of the input
        - hidden_dim: An integer giving the size of the hidden layer
        - num_classes: An integer giving the number of classes to classify
        - weight_scale: Scalar giving the standard deviation for random
          initialization of the weights.
        - reg: Scalar giving L2 regularization strength.
        """
        self.params = {}
        self.params['W1'] = weight_scale * np.random.randn(input_dim, hidden_dim)
        self.params['b1'] = np.zeros(hidden_dim)
        self.params['W2'] = weight_scale * np.random.randn(hidden_dim, num_classes)
        self.params['b2'] = np.zeros(num_classes)
        self.reg = reg

    def loss(self, X, y=None):
        """
        Compute loss and gradient for a minibatch of data.

        Inputs:
        - X: Array of input data of shape (N, d_1, ..., d_k)
        - y: Array of labels, of shape (N,). y[i] gives the label for X[i].

        Returns:
        If y is None, then run a test-time forward pass of the model and return:
        - scores: Array of shape (N, C) giving classification scores, where
          scores[i, c] is the classification score for X[i] and class c.

        If y is not None, then run a training-time forward and backward pass and
        return a tuple of:
        - loss: Scalar value giving the loss
        - grads: Dictionary with the same keys as self.params, mapping parameter
          names to gradients of the loss with respect to those parameters.
        """
        scores = None

        out_affine_relu, cache_affine_relu = affine_relu_forward(X, self.params['W1'], self.params['b1'])
        out_affine, cache_affine = affine_forward(out_affine_relu, self.params['W2'], self.params['b2'])
        scores = out_affine.copy()

        # If y is None then we are in test mode so just return scores
        if y is None:
            return scores

        loss, grads = 0, {}

        loss, dx_softmax = softmax_loss(out_affine, y)
        dx_affine, dW2, db2 = affine_backward(dx_softmax, cache_affine)
        dx, dW1, db1 = affine_relu_backward(dx_affine, cache_affine_relu)

        dW1 += 1 * self.reg * self.params['W1']
        dW2 += 1 * self.reg * self.params['W2']

        grads['W1'] = dW1
        grads['W2'] = dW2
        grads['b1'] = db1
        grads['b2'] = db2

        loss += 0.5 * self.reg * np.sum(self.params['W1'] * self.params['W1'])
        loss += 0.5 * self.reg * np.sum(self.params['W2'] * self.params['W2'])

        return loss, grads


class FullyConnectedNet(object):
    """
    A fully-connected neural network with an arbitrary number of hidden layers,
    ReLU nonlinearities, and a softmax loss function. This will also implement
    dropout and batch/layer normalization as options. For a network with L layers,
    the architecture will be

    {affine - [batch/layer norm] - relu - [dropout]} x (L - 1) - affine - softmax

    where batch/layer normalization and dropout are optional, and the {...} block is
    repeated L - 1 times.

    Similar to the TwoLayerNet above, learnable parameters are stored in the
    self.params dictionary and will be learned using the Solver class.
    """

    def __init__(self, hidden_dims, input_dim=3*32*32, num_classes=10,
                 dropout=1, normalization=None, reg=0.0,
                 weight_scale=1e-2, dtype=np.float32, seed=None):
        """
        Initialize a new FullyConnectedNet.

        Inputs:
        - hidden_dims: A list of integers giving the size of each hidden layer.
        - input_dim: An integer giving the size of the input.
        - num_classes: An integer giving the number of classes to classify.
        - dropout: Scalar between 0 and 1 giving dropout strength. If dropout=1 then
          the network should not use dropout at all.
        - normalization: What type of normalization the network should use. Valid values
          are "batchnorm", "layernorm", or None for no normalization (the default).
        - reg: Scalar giving L2 regularization strength.
        - weight_scale: Scalar giving the standard deviation for random
          initialization of the weights.
        - dtype: A numpy datatype object; all computations will be performed using
          this datatype. float32 is faster but less accurate, so you should use
          float64 for numeric gradient checking.
        - seed: If not None, then pass this random seed to the dropout layers. This
          will make the dropout layers deteriminstic so we can gradient check the
          model.
        """
        self.normalization = normalization
        self.use_dropout = dropout != 1
        self.reg = reg
        self.num_layers = 1 + len(hidden_dims)
        self.dtype = dtype
        self.params = {}

        self.params['W1'] = weight_scale * np.random.randn(input_dim, hidden_dims[0])
        self.params['b1'] = np.zeros(hidden_dims[0])
        self.params['W' + str(self.num_layers)] = weight_scale * np.random.randn(hidden_dims[-1], num_classes)
        self.params['b' + str(self.num_layers)] = np.zeros(num_classes)
        for i in range(len(hidden_dims)):
            if i == 0:
                continue;
            self.params['W' + str(i + 1)] = weight_scale * np.random.randn(hidden_dims[i - 1], hidden_dims[i])
            self.params['b' + str(i + 1)] = np.zeros(hidden_dims[i])

        ############################################################################
        # Initialize the parameters of the network, storing all values in          #
        # the self.params dictionary. Store weights and biases for the first layer #
        # in W1 and b1; for the second layer use W2 and b2, etc. Weights should be #
        # initialized from a normal distribution centered at 0 with standard       #
        # deviation equal to weight_scale. Biases should be initialized to zero.   #
        #                                                                          #
        # When using batch normalization, store scale and shift parameters for the #
        # first layer in gamma1 and beta1; for the second layer use gamma2 and     #
        # beta2, etc. Scale parameters should be initialized to ones and shift     #
        # parameters should be initialized to zeros.                               #
        ############################################################################
        
        if self.normalization == 'batchnorm' or self.normalization == 'layernorm':
            for i in range(len(hidden_dims)):
                self.params['gamma' + str(i + 1)] = np.ones(hidden_dims[i])
                self.params['beta' + str(i + 1)] = np.zeros(hidden_dims[i])

        # When using dropout we need to pass a dropout_param dictionary to each
        # dropout layer so that the layer knows the dropout probability and the mode
        # (train / test). You can pass the same dropout_param to each dropout layer.
        self.dropout_param = {}
        if self.use_dropout:
            self.dropout_param = {'mode': 'train', 'p': dropout}
            if seed is not None:
                self.dropout_param['seed'] = seed

        # With batch normalization we need to keep track of running means and
        # variances, so we need to pass a special bn_param object to each batch
        # normalization layer. You should pass self.bn_params[0] to the forward pass
        # of the first batch normalization layer, self.bn_params[1] to the forward
        # pass of the second batch normalization layer, etc.
        self.bn_params = []
        if self.normalization=='batchnorm':
            self.bn_params = [{'mode': 'train'} for i in range(self.num_layers - 1)]
        if self.normalization=='layernorm':
            self.bn_params = [{} for i in range(self.num_layers - 1)]


        # Cast all parameters to the correct datatype
        for k, v in self.params.items():
            self.params[k] = v.astype(dtype)


    def loss(self, X, y=None):
        """
        Compute loss and gradient for the fully-connected net.

        Input / output: Same as TwoLayerNet above.
        """
        X = X.astype(self.dtype)
        mode = 'test' if y is None else 'train'

        # Set train/test mode for batchnorm params and dropout param since they
        # behave differently during training and testing.
        if self.use_dropout:
            self.dropout_param['mode'] = mode
        if self.normalization=='batchnorm':
            for bn_param in self.bn_params:
                bn_param['mode'] = mode
        scores = None

        caches = []
        for i in range(self.num_layers - 1):
            idx = str(i + 1)
            if i == 0:
                out_ar = X
            if self.normalization == 'batchnorm':
                out_ar, c_ar = affine_bn_relu_forward(out_ar, self.params['W' + idx], self.params['b' + idx], self.params['gamma' + idx] , self.params['beta' + idx], self.bn_params[i])
            elif self.normalization == 'layernorm':
                out_ar, c_ar = affine_ln_relu_forward(out_ar, self.params['W' + idx], self.params['b' + idx], self.params['gamma' + idx] , self.params['beta' + idx], self.bn_params[i])
            else:
                out_ar, c_ar = affine_relu_forward(out_ar, self.params['W' + idx], self.params['b' + idx])

            if self.use_dropout:
                out_ar, c_dr = dropout_forward(out_ar, self.dropout_param)
                caches.append((c_ar, c_dr))
            else:
                caches.append(c_ar)

        idx = str(self.num_layers)
        out_affine, c_ar = affine_forward(out_ar, self.params['W' + idx], self.params['b' + idx])
        caches.append(c_ar)

        scores = out_affine.copy()

        ############################################################################
        # Implement the forward pass for the fully-connected net, computing        #
        # the class scores for X and storing them in the scores variable.          #
        #                                                                          #
        # When using dropout, you'll need to pass self.dropout_param to each       #
        # dropout forward pass.                                                    #
        #                                                                          #
        # When using batch normalization, you'll need to pass self.bn_params[0] to #
        # the forward pass for the first batch normalization layer, pass           #
        # self.bn_params[1] to the forward pass for the second batch normalization #
        # layer, etc.                                                              #
        ############################################################################
       
        # If test mode return early
        if mode == 'test':
            return scores

        loss, grads = 0.0, {}

        loss, dx_softmax = softmax_loss(out_affine, y)

        dx_affine, grads['W' + idx], grads['b' + idx] = affine_backward(dx_softmax, caches[-1])

        for i in range(self.num_layers - 1, 0, -1):
            CACHE = caches[i - 1]

            if self.use_dropout:
                CACHE = caches[i - 1][0]
                dx_affine = dropout_backward(dx_affine, caches[i - 1][1])

            if self.normalization == 'batchnorm':
                dx_affine, grads['W' + str (i)], grads['b' + str(i)], grads['gamma' + str(i)], grads['beta' + str(i)] = affine_bn_relu_backward(dx_affine, CACHE)
            elif self.normalization == 'layernorm':
                dx_affine, grads['W' + str (i)], grads['b' + str(i)], grads['gamma' + str(i)], grads['beta' + str(i)] = affine_ln_relu_backward(dx_affine, CACHE)
            else:
                dx_affine, grads['W' + str (i)], grads['b' + str(i)] = affine_relu_backward(dx_affine, CACHE) 


        for i in range(1, self.num_layers + 1):
            grads['W' + str(i)] += self.reg * self.params['W' + str(i)]


        for i in range(1, self.num_layers + 1):
            loss += 0.5 * self.reg * np.sum(self.params['W' + str(i)] * self.params['W' + str(i)])

        ############################################################################
        # Implement the backward pass for the fully-connected net. Store the       #
        # loss in the loss variable and gradients in the grads dictionary. Compute #
        # data loss using softmax, and make sure that grads[k] holds the gradients #
        # for self.params[k]. Don't forget to add L2 regularization!               #
        #                                                                          #
        # When using batch/layer normalization, you don't need to regularize the scale   #
        # and shift parameters.                                                    #
        #                                                                          #
        # NOTE: To ensure that your implementation matches ours and you pass the   #
        # automated tests, make sure that your L2 regularization includes a factor #
        # of 0.5 to simplify the expression for the gradient.                      #
        ############################################################################

        return loss, grads
