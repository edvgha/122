from collections import defaultdict
import json
import numpy as np
import os
import pandas as pd
from torch_shallow_neural_classifier import TorchShallowNeuralClassifier
import nli
import utils
from sklearn.linear_model import LogisticRegression

DATA_HOME = 'data'

NLIDATA_HOME = os.path.join(DATA_HOME, 'nlidata')

wordentail_filename = os.path.join(
    NLIDATA_HOME, 'nli_wordentail_bakeoff_data.json')

GLOVE_HOME = os.path.join(DATA_HOME, 'glove.6B')

with open(wordentail_filename) as f:
    wordentail_data = json.load(f)

def randvec(w, n=50, lower=-1.0, upper=1.0):
    """Returns a random vector of length `n`. `w` is ignored."""
    return utils.randvec(n=n, lower=lower, upper=upper)


def load_glove50():
    glove_src = os.path.join(GLOVE_HOME, 'glove.6B.50d.txt')
    # Creates a dict mapping strings (words) to GloVe vectors:
    GLOVE = utils.glove2dict(glove_src)
    return GLOVE

GLOVE = load_glove50()

def glove_vec(w):
    """Return `w`'s GloVe representation if available, else return
    a random vector."""
    return GLOVE.get(w, randvec(w, n=50))

def vec_concatenate(u, v):
    """Concatenate np.array instances `u` and `v` into a new np.array"""
    return np.concatenate((u, v))

net = TorchShallowNeuralClassifier(early_stopping=True)

baseline_experiment = nli.wordentail_experiment(
    train_data=wordentail_data['train'],
    assess_data=wordentail_data['dev'],
    model=LogisticRegression(random_state=0),
    vector_func=glove_vec,
    vector_combo_func=vec_concatenate)
