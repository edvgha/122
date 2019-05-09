import matplotlib.pyplot as plt
import setup_problem
from sklearn.base import BaseEstimator, RegressorMixin
from sklearn.datasets.samples_generator import make_blobs
import numpy as np
import nodes
import graph
#import plot_utils

class Multiclass(BaseEstimator, RegressorMixin):
    """ Multiclass with computation graph """
    def __init__(self, num_categories, init_param_scale=.01, step_size=.005,  max_num_epochs = 5000):
        self.num_categories = num_categories
        self.init_param_scale=init_param_scale
        self.step_size = step_size
        self.max_num_epochs = max_num_epochs

        # Build computation graph
        self.x = nodes.ValueNode(node_name="x") # to hold a vector input
        self.y = nodes.ValueNode(node_name="y") # to hold a scalar response
        self.w = nodes.ValueNode(node_name="w") # to hold the parameter vector
        self.b = nodes.ValueNode(node_name="b") # to hold the bias parameter (scalar)

        self.affine = nodes.VectorScalarAffineNode(x=self.x, w=self.w, b=self.b, node_name="Affine")
        self.prediction = nodes.SoftMax(a=self.affine, node_name="SoftMax")

        self.objective = nodes.NegLogLikelihood(a=self.prediction, y=self.y, node_name="NegLogLikelihood")

        # Group nodes into types to construct computation graph function
        self.inputs = [self.x]
        self.outcomes = [self.y]
        self.parameters = [self.w, self.b]

        self.graph = graph.ComputationGraphFunction(self.inputs, self.outcomes,
                                                    self.parameters, self.prediction,
                                                    self.objective)

    def fit(self, X, y):
        num_instances, num_ftrs = X.shape
        y = y.reshape(-1)

        #init_parameter_values = {"w": self.init_param_scale * np.random.randn(self.num_categories, num_ftrs),
        #                         "b": self.init_param_scale * np.random.randn(self.num_categories)}
        init_parameter_values = {"w": self.init_param_scale * np.zeros((self.num_categories, num_ftrs)),
                                 "b": self.init_param_scale * np.zeros(self.num_categories)}
        self.graph.set_parameters(init_parameter_values)

        for epoch in range(self.max_num_epochs):
            shuffle = np.random.permutation(num_instances)
            epoch_obj_tot = 0.0
            for j in shuffle:
                obj, grads = self.graph.get_gradients(input_values = {"x": X[j]},
                                                    outcome_values = {"y": y[j]})
                #print(obj)
                epoch_obj_tot += obj
                # Take step in negative gradient direction
                steps = {}
                for param_name in grads:
                    steps[param_name] = -self.step_size * grads[param_name]
                    self.graph.increment_parameters(steps)
                #pdb.set_trace()

            if epoch % 5 == 0:
                print("Epoch ",epoch,": average objective value=",epoch_obj_tot/num_instances)

    def predict(self, X, y=None):
        try:
            getattr(self, "graph")
        except AttributeError:
            raise RuntimeError("You must train classifer before predicting data!")

        num_instances = X.shape[0]
        preds = np.zeros(num_instances)
        for j in range(num_instances):
            preds[j] = np.argmax(self.graph.get_prediction(input_values={"x":X[j]}))

        return preds


def main():
    np.random.seed(2)
    X, y = make_blobs(n_samples=300,cluster_std=.25, centers=np.array([(-3,1),(0,2),(3,1)]))
    #plt.scatter(X[:, 0], X[:, 1], c=y, s=50)

    estimator = Multiclass(num_categories=3, init_param_scale=0.01, step_size=0.001, max_num_epochs=100)
    estimator.fit(X, y)

    h = .02  # step size in the mesh
    x_min, x_max = min(X[:,0])-3,max(X[:,0])+3
    y_min, y_max = min(X[:,1])-3,max(X[:,1])+3
    xx, yy = np.meshgrid(np.arange(x_min, x_max, h),np.arange(y_min, y_max, h))
    mesh_input = np.c_[xx.ravel(), yy.ravel()]

    Z = estimator.predict(mesh_input)

    Z = Z.reshape(xx.shape)
    plt.contourf(xx, yy, Z, cmap=plt.cm.coolwarm, alpha=0.8)
    plt.scatter(X[:, 0], X[:, 1], c=y, cmap=plt.cm.coolwarm)

    #from sklearn import metrics
    #metrics.confusion_matrix(y, estimator.predict(X))
    plt.show()


if __name__ == '__main__':
  main()
