# PCA (sklearn.decomposition vs Eigen(C++))

## Method for generating dataset in PCA with sklearn.decomposition

To generate dataset, we used `np.rand.rand` that uses the parameters `(m,n)` to generate a
random dataset of `(m,n)` dimensions which are essentially values between 0 and 1.

## Runtime for PCA using sklearn.decomposition

The runtime for the implementation of PCA using `sklearn.decomposition` can be checked by
running the code in the `.ipynb` file. For my device, the implementation didn’t run for the datasets
beyond the dimensions `(10000,10000)` due to processing constraints.

The runtimes for the datasets until `(10000,10000)` are:

- Dataset Dimensions: `(100, 100)`, PCA components: 10, Runtime: 0.08 seconds
- Dataset Dimensions: `(1000, 1000)`, PCA components: 100, Runtime: 0.08 seconds
- Dataset Dimensions: `(10000, 10000)`, PCA components: 1000, Runtime: 38.91 seconds

## Method for generating dataset for PCA using Eigen library in C++

To generate dataset using Eigen, we use a standard library function `random_device` and use
`mt19937` which is a popular random number generator from 0-1 with uniform distribution (same
as the `np.random.rand`). We iterate it over the dimensions `(m,n)`.

## Runtime for PCA using Eigen library in C++

The runtime for PCA using Eigen library in C++ was measured using the library ‘chrono’ which
measures elapsed time in between it’s start and end points. Like the above case, due to the
memory constraints, the program crashed for datasets above `(1000,1000)`.

The runtimes for the datasets until `(1000,1000)` at the time of implementation are:

- Dataset `(100, 100)` PCA result: `(100, 10)`, Elapsed time: 43 ms (0.043 s)
- Dataset `(1000, 1000)` PCA result: `(1000, 100)`, Elapsed time: 33186 ms (33.186 s)

## Conclusion

In terms of runtime only, the `sklearn.decomposition` library worked faster for larger datasets but
it can have multiple reasons like the `sklearn.decomposition` method had mostly used pre-built
functions to generate random dataset and do PCA (which uses optimization methods) while the
C++ code was more manual without optimizing the algorithm or use parallelization methods.
