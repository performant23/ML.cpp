# Multidimensional Scaling (MDS) Performance Comparison

This project compares the execution times of Multidimensional Scaling (MDS) algorithms implemented in Python and C++. MDS is a technique used for visualizing the level of similarity of individual sample points in multidimensional data.

## Data Generation

The input data for both Python and C++ implementations is randomly generated. Specifically, for each dimension (e.g., 2x2, 5x5, ..., 1000x1000), a random matrix `X` is generated, where each element is drawn from a uniform distribution.

## Algorithms

### Python Implementation

The Python implementation of MDS uses NumPy for numerical computation and SciPy for computing pairwise Euclidean distances. The MDS algorithm follows these steps:
1. Compute pairwise Euclidean distances between data points using the `pdist` function from SciPy.
2. Compute the double-centered matrix `B`.
3. Perform eigen decomposition of `B`.
4. Select the desired number of dimensions and scale the coordinates to match the original distances.

### C++ Implementation

The C++ implementation of MDS uses the Eigen library for linear algebra operations. The steps of the MDS algorithm are similar to the Python implementation:


## Execution Time Comparison

Python's execution time is significantly faster compared to C++. This can be because Python has lower overhead in terms of memory management and startup time and also the code used in Python comes from highly optimized standard libraries. C++ might be able to provide comparable performance if optimized further.

The Execution times observed are as follows:

Python:
```
Dimensions: 2, Execution time: 0.000486374 seconds
Dimensions: 5, Execution time: 0.000325680 seconds
Dimensions: 10, Execution time: 0.000278711 seconds
Dimensions: 50, Execution time: 0.006472588 seconds
Dimensions: 100, Execution time: 0.017113924 seconds
Dimensions: 500, Execution time: 0.199403524 seconds
Dimensions: 1000, Execution time: 0.885557890 seconds
```

C++
```
Dimensions: 2, Execution time: 0.000000000 seconds 
Dimensions: 5, Execution time: 0.000000000 seconds 
Dimensions: 10, Execution time: 0.000000000 seconds 
Dimensions: 50, Execution time: 0.016781500 seconds 
Dimensions: 100, Execution time: 0.062866000 seconds 
Dimensions: 500, Execution time: 5.036669100 seconds 
Dimensions: 1000, Execution time: 39.228096600 seconds
```