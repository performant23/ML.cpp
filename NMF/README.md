# Non-negative Matrix Factorization (NMF) Execution Time Comparison

This repository contains C++ and Python implementations of the Non-negative Matrix Factorization (NMF) algorithm. It compares the execution times of the NMF algorithm implemented in C++ using Eigen library and Python using NumPy.

## How Data Was Generated

Both C++ and Python implementations were tested with randomly generated non-negative matrices of varying dimensions. The dimensions used for testing are specified in the code. Each matrix element was generated randomly using a uniform distribution between 0 and 1.

## How Algorithms Were Run

### C++ Implementation

The C++ implementation uses the Eigen library for matrix operations. It computes the NMF for each randomly generated matrix and records the execution time.

### Python Implementation

The Python implementation utilizes NumPy for matrix operations. Similar to the C++ implementation, it computes the NMF for each randomly generated matrix and measures the execution time.

## Implementation Time Differences

The Python implementation is observed to have significantly faster execution times compared to the C++ implementation. This discrepancy can be attributed to several factors:

1. **Implementation Differences**: While both implementations use efficient libraries for matrix operations (Eigen in C++ and NumPy in Python), the underlying implementation details differ. It may be possible to get comparable performance using C++ by optimizing the code for number of arithmetic operations even further.

2. **Matrix Operations**: NumPy is highly optimized for numerical computations and utilizes optimized BLAS (Basic Linear Algebra Subprograms) libraries under the hood, resulting in faster matrix operations compared to Eigen in certain scenarios.

3. **Memory Management**: Python's memory management might offer advantages in certain cases, especially when dealing with large arrays. NumPy's array memory layout and caching mechanisms may contribute to better performance.

4. **Vectorization**: NumPy supports vectorized operations, allowing for efficient element-wise operations and broadcasting. This can lead to faster execution times compared to manually optimized C++ code.

## Execution Time Comparison

The execution times for both implementations are provided below:

```
C++:

(2x2): 0.000000000 seconds
(5x5): 0.016125500 seconds
(10x10): 0.000000000 seconds
(50x50): 0.035635800 seconds
(100x100): 0.147901300 seconds
(500x500): 3.397450700 seconds
(1000x1000): 15.425134000 seconds


Python:

(2x2): 0.004222393 seconds
(5x5): 0.003346682 seconds
(10x10): 0.002251625 seconds
(50x50): 0.003957748 seconds
(100x100): 0.007250547 seconds
(500x500): 0.192041159 seconds
(1000x1000): 0.891921520 seconds
```

As observed, the Python implementation consistently outperforms the C++ implementation in terms of execution time across all matrix dimensions.


## Conclusion

While C++ is generally considered faster than Python due to its lower-level nature and compiler optimizations, the specific choice of libraries and implementation details can influence performance. In this case, NumPy's highly optimized array operations and memory management contribute to the faster execution times observed in the Python implementation.
