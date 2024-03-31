# -*- coding: utf-8 -*-
import numpy as np
from scipy.linalg import svd
from scipy.spatial.distance import pdist, squareform
import time
import numpy.lib.scimath as scimath

def computeDistances(X):
    return squareform(pdist(X, 'euclidean'))

# Multidimensional Scaling (MDS)
def mds(D, d):
    n = D.shape[0]

    H = np.eye(n) - np.ones((n, n)) / n
    B = -0.5 * H @ D @ H

    U, Sigma, VT = svd(B)

    Z_full = U[:, :d]

    S = Z_full.T @ D @ Z_full
    Lambda_sqrt_inv = np.diag(1 / scimath.sqrt(np.diag(S)))
    Z = Z_full @ Lambda_sqrt_inv

    return Z

dimensions = [2, 5, 10, 50, 100, 500, 1000]
for dim in dimensions:
    X = np.random.rand(dim, 3)
    D = computeDistances(X)
    d = 2

    start = time.time()
    Z = mds(D, d)
    finish = time.time()
    elapsed = finish - start

    print(f"Dimensions: {dim}")
    print(f"Execution time: {elapsed:.9f} seconds")