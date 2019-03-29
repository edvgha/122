import numpy as np
import pandas as pd
from sklearn.base import BaseEstimator, RegressorMixin
from scipy.optimize import minimize

class LogisticRegression(BaseEstimator, RegressorMixin):
    """ Logistic Regression """

    def __init__(self, l2reg = 1):
        if l2reg < 0:
            raise ValueError('Regularization penalty should be at least 0.')
        self.l2reg = l2reg

    def fit(self, X, y = None):
        n, num_ftrs = X.shape
        y = y.reshape(-1)
        def logistic_obj(w):
            l2_norm_squared = np.sum(w**2)
            y_new = (y - 1) + y
            e = -1 * y_new * np.dot(X,w)
            z = np.zeros(n)
            M = np.maximum(z, e)
            log_likelihood = np.sum(M + np.logaddexp(-M, e - M))/n
            objective = log_likelihood + self.l2reg * l2_norm_squared
            return objective
        self.logistic_obj_ = logistic_obj

        w_0 = np.zeros(num_ftrs)

        self.w_ = minimize(logistic_obj, w_0).x
        return self

    def predict(self, X, y=None):
        #η = <w,x>
        #φ(η) = 1/ (1 + e^−η )
        try:
            getattr(self, "w_")
        except AttributeError:
            raise RuntimeError("You must train classifer before predicting data!")
        return 1 / (1 + np.exp(-1 * np.dot(X, self.w_)))

    def score(self, X, y):
        # Average square error
        try:
            getattr(self, "w_")
        except AttributeError:
            raise RuntimeError("You must train classifer before predicting data!")
        return -np.sum(np.log(abs(self.predict(X) - abs(y - 1)))) / len(y)

def main():

    #Load data
    X_train_pandas = pd.read_csv("X_train.csv")
    X_val_pandas = pd.read_csv("X_val.csv");
    y_train = np.loadtxt("y_train.txt")
    y_val = np.loadtxt("y_val.txt")

    ### Normalize
    X_train_pandas.apply(lambda x: (x - np.mean(x)) / (np.max(x) - np.min(x)))
    X_val_pandas.apply(lambda x: (x - np.mean(x)) / (np.max(x) - np.min(x)))

    ### Add bias column
    sLength = len(X_train_pandas['a'])
    X_train_pandas = X_train_pandas.assign(u=pd.Series(np.ones(sLength)).values)
    sLength = len(X_val_pandas['a'])
    X_val_pandas = X_val_pandas.assign(u=pd.Series(np.ones(sLength)).values)

    ### Pick l2 regularizator
    l2regs = np.unique(np.concatenate((10.**np.arange(-6,1,1),np.arange(1,3,.3))))
    sc_min = 100000
    l2 = 0
    preds = []
    for l2reg in l2regs:
        log_reg = LogisticRegression(l2reg=l2reg)
        log_reg.fit(X_train_pandas.values, y_train)
        name = "Logistic with L2Reg="+str(l2reg)
        sc = log_reg.score(X_train_pandas.values, y_train)
        if sc_min > sc:
            sc_min = sc
            l2 = l2reg

    logistic_regression = LogisticRegression(l2reg=l2)
    logistic_regression.fit(X_train_pandas.values, y_train)
    y_proba = logistic_regression.predict(X_val_pandas.values)

    n = len(y_proba)
    good_1 = 0; good_0 = 0
    bad_1 = 0; bad_0 = 0
    for i in range(0, n):
        if y_val[i] == 1 and y_proba[i] > 0.5:
            good_1 += 1
        elif y_val[i] == 1 and y_proba[i] < 0.5:
            bad_1 += 1
        elif y_val[i] == 0 and y_proba[i] < 0.5:
            good_0 += 1
        elif y_val[i] == 0 and y_proba[i] > 0.5:
            bad_0 += 1
    print ("good_1:", good_1)
    print ("good_0:", good_0)
    print ("bad_1:", bad_1)
    print ("bad_0:", bad_0)

if __name__ == '__main__':
    main()
