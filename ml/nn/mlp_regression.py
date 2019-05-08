import matplotlib.pyplot as plt
import setup_problem
from sklearn.base import BaseEstimator, RegressorMixin
import numpy as np
import nodes
import graph
import plot_utils
#import pdb
#pdb.set_trace()  #useful for debugging!


class MLPRegression(BaseEstimator, RegressorMixin):
    """ MLP regression with computation graph """
    def __init__(self, num_hidden_units=10, step_size=.005, init_param_scale=0.01, max_num_epochs = 5000):
        self.num_hidden_units = num_hidden_units
        self.init_param_scale = 0.01
        self.max_num_epochs = max_num_epochs
        self.step_size = step_size

        # Build computation graph

        #Data
        self.x = nodes.ValueNode(node_name="x") # to hold a vector input
        self.y = nodes.ValueNode(node_name="y") # to hold a scalar response

        #Parameters
        self.W1 = nodes.ValueNode(node_name="W1")
        self.b1 = nodes.ValueNode(node_name="b1")
        self.W2 = nodes.ValueNode(node_name="W2")
        self.b2 = nodes.ValueNode(node_name="b2")

        #Hiddel layers
        self.AffineHiddenLayer = nodes.AffineNode(x=self.x, W=self.W1, b=self.b1, node_name="AffineHiddenLayer")
        self.Tanh = nodes.TanhNode(a=self.AffineHiddenLayer, node_name="TanhHiddenLayer")

        #Prediction
        self.prediction = nodes.AffineNode(x=self.Tanh, W=self.W2, b=self.b2, node_name="Prediction")

        #Objective
        self.objective = nodes.SquaredL2DistanceNode(a=self.prediction, b=self.y, node_name="SquareLoss")

        # Group nodes into types to construct computation graph function
        self.inputs = [self.x]
        self.outcomes = [self.y]
        self.parameters = [self.W1, self.b1, self.W2, self.b2]

        self.graph = graph.ComputationGraphFunction(self.inputs, self.outcomes,
                                                    self.parameters, self.prediction,
                                                    self.objective)

    def fit(self, X, y):
        num_instances, num_ftrs = X.shape
        y = y.reshape(-1)

        print ("NUM HIDDEN UNITS:", self.num_hidden_units)
        print ("NUM FEATURES:", num_ftrs)

        s = self.init_param_scale
        m = self.num_hidden_units
        d = num_ftrs

        init_values = {"W1": s * np.random.randn(m, d), "b1": s * np.random.randn(m),
                       "W2": s * np.random.randn(1, m), "b2": np.array(s * np.random.randn(1))}

        self.graph.set_parameters(init_values)

        for epoch in range(self.max_num_epochs):
            shuffle = np.random.permutation(num_instances)
            epoch_obj_tot = 0.0
            for j in shuffle:
                obj, grads = self.graph.get_gradients(input_values = {"x": X[j]},
                                                    outcome_values = {"y": y[j]})
                epoch_obj_tot += obj
                # Take step in negative gradient direction
                steps = {}
                for param_name in grads:
                    steps[param_name] = -self.step_size * grads[param_name]
                    self.graph.increment_parameters(steps)

            if epoch % 50 == 0:
                train_loss = sum((y - self.predict(X,y)) **2)/num_instances
                print("Epoch ",epoch,": Ave objective=",epoch_obj_tot/num_instances," Ave training loss: ",train_loss)

    def predict(self, X, y=None):
        try:
            getattr(self, "graph")
        except AttributeError:
            raise RuntimeError("You must train classifer before predicting data!")

        num_instances = X.shape[0]
        preds = np.zeros(num_instances)
        for j in range(num_instances):
            preds[j] = self.graph.get_prediction(input_values={"x":X[j]})

        return preds



def main():
    lasso_data_fname = "lasso_data.pickle"
    x_train, y_train, x_val, y_val, target_fn, coefs_true, featurize = setup_problem.load_problem(lasso_data_fname)

    # Generate features
    X_train = featurize(x_train)
    X_val = featurize(x_val)

    # Let's plot prediction functions and compare coefficients for several fits
    # and the target function.
    pred_fns = []
    x = np.sort(np.concatenate([np.arange(0,1,.001), x_train]))

    pred_fns.append({"name": "Target Parameter Values (i.e. Bayes Optimal)", "coefs": coefs_true, "preds": target_fn(x)})

    estimator = MLPRegression(num_hidden_units=10, step_size=0.001, init_param_scale=.0005,  max_num_epochs=5000)
    x_train_as_column_vector = x_train.reshape(x_train.shape[0],1) # fit expects a 2-dim array
    x_as_column_vector = x.reshape(x.shape[0],1) # fit expects a 2-dim array
    estimator.fit(x_train_as_column_vector, y_train)
    name = "MLP regression - no features"
    pred_fns.append({"name":name, "preds": estimator.predict(x_as_column_vector) })

    X = featurize(x)
    estimator = MLPRegression(num_hidden_units=10, step_size=0.0005, init_param_scale=.01,  max_num_epochs=500)
    estimator.fit(X_train, y_train)
    name = "MLP regression - with features"
    pred_fns.append({"name":name, "preds": estimator.predict(X) })
    plot_utils.plot_prediction_functions(x, pred_fns, x_train, y_train, legend_loc="best")

if __name__ == '__main__':
  main()
