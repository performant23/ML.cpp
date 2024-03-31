# ML Algorithms Runtime Comparison

This project aims to implement common algorithms like SVD, MDS, PCA, and NMF in C++ using the library 'Eigen'. 

We also compared the execution times of common machine learning algorithms implemented in Python and C++. The algorithms considered for comparison include Multidimensional Scaling (MDS), Principal Component Analysis (PCA), Non-negative Matrix Factorization (NMF), and Singular Value Decomposition (SVD). The implementations were tested on randomly generated datasets of varying dimensions to evaluate their performance.

It was observed that, in all algorithms, using the standard libraries in Python gave better execution runtimes. This could be due to various reasons including the level of optimization obtained due to use of NumPy arrays instead of traditional matrices and also due to the fact that libraries like `sklearn` use Cython for performance. 

Optimizing the algorithms in C++ for runtimes by reducing I/O and storage, memory allocation and deallocation (for example, using smart pointers), using optimized data structures, utilize multi-threading and use optimization techniques like loop unrolling, inlining, and vectorization, etc. can be explored further for a better comparison.
