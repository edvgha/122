import numpy as np
from numpy import linalg as la

def f_objective(theta, X, y, l2_param=1):
    '''
    Args:
        theta: 1D numpy array of size num_features
        X: 2D numpy array of size (num_instances, num_features)
        y: 1D numpy array of size num_instances
        l2_param: regularization parameter

    Returns:
        objective: scalar value of objective function
    '''
    n, ys = X.shape
    print ("valod:", y.shape, (np.dot(X, theta)).reshape(-1).shape)
    e = y.reshape((n,1)) * (np.dot(X, theta)).T
    z = np.zeros(n)
    M = np.max(e, z)
    empirical_risk = np.sum(M + np.logaddexp(-M, e - M))/n
    l2_norm_squared = np.sum(theta**2)
    return empirical_risk + l2_norm_squared


   #acc = 0
   #for i in range(0, xs):
   #    exp = -1 * y[i] * np.dot(X[i], theta)
   #    M = max(0, exp);
   #    acc = acc + (M + np.logaddexp(-M, exp - M));
   #return (1.0/xs) * acc + l2_param * la.norm(theta, 2)

def fit_logistic_reg(X, y, objective_function, l2_param=1):
    '''
    Args:
        X: 2D numpy array of size (num_instances, num_features)
        y: 1D numpy array of size num_instances
        objective_function: function returning the value of the objective
        l2_param: regularization parameter

    Returns:
        optimal_theta: 1D numpy array of size num_features
    '''

def main():
    theta = np.array([1, 1, 1])
    X = np.matrix([[1,1,1], [2,2,2]])
    y = np.array([1, -1])
    l2_param = 0.5
    print (f_objective(theta, X, y, l2_param))

if __name__ == '__main__':
    main()
