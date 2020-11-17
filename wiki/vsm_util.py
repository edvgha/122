import numpy as np
import pandas as pd
import argparse
import scipy
import scipy.spatial.distance

def load_data_frame():
    parser = argparse.ArgumentParser()
    parser.add_argument('--vectors_file', default='output/arm_vectors.txt', type=str)
    args = parser.parse_args()

    with open(args.vectors_file, 'r') as f:
        vectors = {}
        for line in f:
            vals = line.rstrip().split(' ')
            vectors[vals[0]] = [float(x) for x in vals[1:]]
        return pd.DataFrame.from_dict(vectors, orient='index')

def euclidean(u, v):
    return scipy.spatial.distance.euclidean(u, v)


def vector_length(u):
    return np.sqrt(u.dot(u))


def length_norm(u):
    return u / vector_length(u)


def cosine(u, v):
    return scipy.spatial.distance.cosine(u, v)


def matching(u, v):
    return np.sum(np.minimum(u, v))


def jaccard(u, v):
    return 1.0 - (matching(u, v) / np.sum(np.maximum(u, v)))


def neighbors(word, df, distfunc=cosine):
    """
    Tool for finding the nearest neighbors of `word` in `df` according
    to `distfunc`. The comparisons are between row vectors.

    Parameters
    ----------
    word : str
        The anchor word. Assumed to be in `rownames`.

    df : pd.DataFrame
        The vector-space model.

    distfunc : function mapping vector pairs to floats (default: `cosine`)
        The measure of distance between vectors. Can also be `euclidean`,
        `matching`, `jaccard`, as well as any other distance measure
        between 1d vectors.

    Raises
    ------
    ValueError
        If word is not in `df.index`.

    Returns
    -------
    pd.Series
        Ordered by closeness to `word`.

    """
    if word not in df.index:
        raise ValueError('{} is not in this VSM'.format(word))
    w = df.loc[word]
    dists = df.apply(lambda x: distfunc(w, x), axis=1)
    return dists.sort_values()


if __name__ == '__main__':
    #df = load_data_frame()
    #df.to_csv('VSM.csv')
    # TODO load from csv
    while True:
        word = input("Enter word ...\n")
        if word in df.index:
            w_df = neighbors(word, df)
            print(w_df.head(11))
        else:
            print("Word is not in vector space\n")
