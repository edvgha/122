import numpy as np
import pandas as pd
from sklearn.base import BaseEstimator, RegressorMixin
from scipy.optimize import minimize
from sklearn.linear_model import LogisticRegression

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

    log_reg = LogisticRegression()
    log_reg.fit(X_train_pandas.values, y_train)
    print ('classes: ', log_reg.classes_)
    y_proba = log_reg.predict_proba(X_val_pandas.values);

    n = len(y_val)
    good_1 = 0; good_0 = 0
    bad_1 = 0; bad_0 = 0
    for i in range(0, n):
        if y_val[i] == 1 and y_proba[i][1] > 0.5:
            good_1 += 1
        elif y_val[i] == 1 and y_proba[i][1] < 0.5:
            bad_1 += 1
        elif y_val[i] == 0 and y_proba[i][0] > 0.5:
            good_0 += 1
        elif y_val[i] == 0 and y_proba[i][0] < 0.5:
            bad_0 += 1
    print ("good_1:", good_1)
    print ("good_0:", good_0)
    print ("bad_1:", bad_1)
    print ("bad_0:", bad_0)

if __name__ == '__main__':
    main()
