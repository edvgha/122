from __future__ import print_function

from builtins import range
from builtins import object
import numpy as np
import matplotlib.pyplot as plt
from past.builtins import xrange

class TwoLayerNet(object):
    """
    A two-layer fully-connected neural network. The net has an input dimension of
    N, a hidden layer dimension of H, and performs classification over C classes.
    We train the network with a softmax loss function and L2 regularization on the
    weight matrices. The network uses a ReLU nonlinearity after the first fully
    connected layer.

    In other words, the network has the following architecture:

    input - fully connected layer - ReLU - fully connected layer - softmax

    The outputs of the second fully-connected layer are the scores for each class.
    """

    def __init__(self, input_size, hidden_size, output_size, std=1e-4):
        """
        Initialize the model. Weights are initialized to small random values and
        biases are initialized to zero. Weights and biases are stored in the
        variable self.params, which is a dictionary with the following keys:

        W1: First layer weights; has shape (D, H)
        b1: First layer biases; has shape (H,)
        W2: Second layer weights; has shape (H, C)
        b2: Second layer biases; has shape (C,)

        Inputs:
        - input_size: The dimension D of the input data.
        - hidden_size: The number of neurons H in the hidden layer.
        - output_size: The number of classes C.
        """
        self.params = {}
        self.params['W1'] = std * np.random.randn(input_size, hidden_size)
        self.params['b1'] = np.zeros(hidden_size)
        self.params['W2'] = std * np.random.randn(hidden_size, output_size)
        self.params['b2'] = np.zeros(output_size)

    def loss(self, X, y=None, reg=0.0):
        """
        Compute the loss and gradients for a two layer fully connected neural
        network.

        Inputs:
        - X: Input data of shape (N, D). Each X[i] is a training sample.
        - y: Vector of training labels. y[i] is the label for X[i], and each y[i] is
          an integer in the range 0 <= y[i] < C. This parameter is optional; if it
          is not passed then we only return scores, and if it is passed then we
          instead return the loss and gradients.
        - reg: Regularization strength.

        Returns:
        If y is None, return a matrix scores of shape (N, C) where scores[i, c] is
        the score for class c on input X[i].

        If y is not None, instead return a tuple of:
        - loss: Loss (data loss and regularization loss) for this batch of training
          samples.
        - grads: Dictionary mapping parameter names to gradients of those parameters
          with respect to the loss function; has the same keys as self.params.
        """
        # Unpack variables from the params dictionary
        W1, b1 = self.params['W1'], self.params['b1']
        W2, b2 = self.params['W2'], self.params['b2']
        N, D = X.shape

        # Compute the forward pass
        scores = None
        #############################################################################
        # Perform the forward pass, computing the class scores for the input.       #
        # Store the result in the scores variable, which should be an array of      #
        # shape (N, C).                                                             #
        #############################################################################

        #Affine node forward
        # W1 = DxH
        # b1 = 1xH
        # X  = NxD
        # n1_out = NxH
        n1_out = np.dot(X, W1) + b1

        #ReLU node forward
        # ReLU_in = NxH
        # ReLU_out = NxH
        ReLU_in = n1_out
        ReLU_out = ReLU_in
        ReLU_out[ReLU_out < 0] = 0

        #Affine node forward
        # n2_in = NxH
        # W2 = HxC
        # b2 = 1xC
        # n2_out = NxC
        n2_in = ReLU_out
        n2_out = np.dot(n2_in, W2) + b2

        scores = n2_out

        # If the targets are not given then jump out, we're done
        if y is None:
            return scores

        # Compute the loss
        loss = None
        #############################################################################
        # Finish the forward pass, and compute the loss. This should include        #
        # both the data loss and L2 regularization for W1 and W2. Store the result  #
        # in the variable loss, which should be a scalar. Use the Softmax           #
        # classifier loss.                                                          #
        #############################################################################

        #Softmax node forward
        # softmax_in = NxC
        # y = 1xN
        # softmax_out = 1xN
        softmax_in = n2_out
        correct_class_score = softmax_in[np.arange(0, N, 1), y]
        normalizer = np.sum(np.exp(softmax_in), axis = 1)
        softmax_out = np.exp(correct_class_score) / normalizer

        #Neg log node forward
        # log_in = 1xN
        # log_out = 1xN
        log_in = softmax_out
        log_out = -np.log(log_in)

        #Loss node forward
        # loss_in = 1xN
        # loss_out = 1x1
        # without reg terms
        loss_in = log_out
        loss_out = np.sum(loss_in) / N

        # Reg term
        loss_out += reg * np.sum(W1 * W1)
        loss_out += reg * np.sum(W2 * W2)
        loss = loss_out


        # Backward pass: compute gradients
        grads = {}
        #############################################################################
        # Compute the backward pass, computing the derivatives of the weights       #
        # and biases. Store the results in the grads dictionary. For example,       #
        # grads['W1'] should store the gradient on W1, and be a matrix of same size #
        #############################################################################

        #NxC
        delta = np.zeros(softmax_in.shape)
        delta[np.arange(0, N, 1), y] = 1
        dSoftmax = (np.exp(softmax_in)/normalizer[:,np.newaxis] - delta)
        dSoftmax /= float(N)

        # dn2 = NxH
        # dW2 = HxC
        # db2 = 1xC
        dW2 = np.dot(n2_in.T, dSoftmax)
        db2 = np.dot(np.ones(N)[np.newaxis,:], dSoftmax)
        dn2 = np.dot(dSoftmax, W2.T)

        #dReLU = NxH
        dReLU = dn2
        dReLU[ReLU_in <= 0] = 0

        # dW1 = DxH
        # db1 = 1xH
        # X  = NxD
        dW1 = np.dot(X.T, dReLU)
        db1 = np.dot(np.ones(N)[np.newaxis,:], dReLU)

        # reg terms 
        dW1 += 2 * reg * W1
        dW2 += 2 * reg * W2

        grads['W1'] = dW1
        grads['W2'] = dW2
        grads['b1'] = db1
        grads['b2'] = db2

        return loss, grads

    def train(self, X, y, X_val, y_val,
              learning_rate=1e-3, learning_rate_decay=0.95,
              reg=5e-6, num_iters=100,
              batch_size=200, verbose=False):
        """
        Train this neural network using stochastic gradient descent.

        Inputs:
        - X: A numpy array of shape (N, D) giving training data.
        - y: A numpy array f shape (N,) giving training labels; y[i] = c means that
          X[i] has label c, where 0 <= c < C.
        - X_val: A numpy array of shape (N_val, D) giving validation data.
        - y_val: A numpy array of shape (N_val,) giving validation labels.
        - learning_rate: Scalar giving learning rate for optimization.
        - learning_rate_decay: Scalar giving factor used to decay the learning rate
          after each epoch.
        - reg: Scalar giving regularization strength.
        - num_iters: Number of steps to take when optimizing.
        - batch_size: Number of training examples to use per step.
        - verbose: boolean; if true print progress during optimization.
        """
        num_train = X.shape[0]
        iterations_per_epoch = max(num_train / batch_size, 1)

        # Use SGD to optimize the parameters in self.model
        loss_history = []
        train_acc_history = []
        val_acc_history = []

        for it in range(num_iters):
            X_batch = None
            y_batch = None

            #########################################################################
            # Create a random minibatch of training data and labels, storing        #
            # them in X_batch and y_batch respectively.                             #
            #########################################################################
            batch_indexes = np.random.choice(range(num_train), batch_size)
            X_batch = X[batch_indexes]
            y_batch = y[batch_indexes]

            # Compute loss and gradients using the current minibatch
            loss, grads = self.loss(X_batch, y=y_batch, reg=reg)
            loss_history.append(loss)

            #########################################################################
            # Use the gradients in the grads dictionary to update the               #
            # parameters of the network (stored in the dictionary self.params)      #
            # using stochastic gradient descent. You'll need to use the gradients   #
            # stored in the grads dictionary defined above.                         #
            #########################################################################
            self.params['W1'] -= learning_rate * grads['W1']
            self.params['b1'] -= learning_rate * np.squeeze(grads['b1'])
            self.params['W2'] -= learning_rate * grads['W2']
            self.params['b2'] -= learning_rate * np.squeeze(grads['b2'])

            if verbose and it % 100 == 0:
                print('iteration %d / %d: loss %f' % (it, num_iters, loss))

            # Every epoch, check train and val accuracy and decay learning rate.
            if it % iterations_per_epoch == 0:
                # Check accuracy
                train_acc = (self.predict(X_batch) == y_batch).mean()
                val_acc = (self.predict(X_val) == y_val).mean()
                train_acc_history.append(train_acc)
                val_acc_history.append(val_acc)

                # Decay learning rate
                learning_rate *= learning_rate_decay

        return {
          'loss_history': loss_history,
          'train_acc_history': train_acc_history,
          'val_acc_history': val_acc_history,
        }

    def predict(self, X):
        """
        Use the trained weights of this two-layer network to predict labels for
        data points. For each data point we predict scores for each of the C
        classes, and assign each data point to the class with the highest score.

        Inputs:
        - X: A numpy array of shape (N, D) giving N D-dimensional data points to
          classify.

        Returns:
        - y_pred: A numpy array of shape (N,) giving predicted labels for each of
          the elements of X. For all i, y_pred[i] = c means that X[i] is predicted
          to have class c, where 0 <= c < C.
        """

        score = self.loss(X, y=None, reg=5e-6)

        y_pred = np.argmax(score, axis=1)

        return y_pred
