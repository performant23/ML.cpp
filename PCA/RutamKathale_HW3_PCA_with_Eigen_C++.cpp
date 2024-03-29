#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <random>
#include <chrono>

// Function to generate random dataset
Eigen::MatrixXd generateRandomDataset(int m, int n) {
  std::random_device rd; //this is a C++ Standard Library function
  std::mt19937 rand_gen(rd()); // mt 19937 is a random number generator
  std::uniform_real_distribution<> d(0, 1); // we generate random numbers between 0-1

  Eigen::MatrixXd dataset(m, n); // Generation for given dimensions
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      dataset(i, j) = d(rand_gen);
    }
  }

  return dataset; // We return a Eigen::MatrixXd object as the dataset
}


Eigen::MatrixXd performPCA(const Eigen::MatrixXd& dataset, int numComponents) {
  // We center the data by subtracting the mean of each column from each element in the column
  Eigen::MatrixXd centered = dataset.rowwise() - dataset.colwise().mean();

  // Compute the covariance matrix 
  //Formula - (X^T * X) / (n - 1), where X is the centered data matrix and n is the number of rows in X. 
  Eigen::MatrixXd cov = (centered.adjoint() * centered) / (dataset.rows() - 1);

  // Compute the eigenvalues and eigenvectors
  Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(cov);
  Eigen::MatrixXd eigenvectors = eigensolver.eigenvectors();

  // Sort the eigenvectors by decreasing eigenvalues
  // We keep top numComponents eigenvectors to form a new matrix
  // This is because Eigenvectors are hierarchical i.e. the top 'x' vectors matter more in a matrix representation
  // In other words, we select the most important 'x' components 
  Eigen::VectorXd eigenvalues = eigensolver.eigenvalues();
  Eigen::MatrixXd sortedEigenvectors(eigenvectors.rows(), numComponents);


  std::vector<std::pair<double, int>> eigenvalueIndexPairs;
  for (int i = 0; i < eigenvalues.size(); ++i) {
    eigenvalueIndexPairs.push_back(std::make_pair(eigenvalues[i], i));
  }
  std::sort(eigenvalueIndexPairs.rbegin(), eigenvalueIndexPairs.rend());

  for (int i = 0; i < numComponents; ++i) {
    sortedEigenvectors.col(i) = eigenvectors.col(eigenvalueIndexPairs[i].second);
  }

  // Finally, we project the centered data onto the selected eigenvectors to obtain the principal components. 
  //and return an Eigen::MatrixXd object representing the projected data.
  Eigen::MatrixXd projectedData = centered * sortedEigenvectors;

  return projectedData;
}



int main() {
  std::vector<std::pair<int, int>> dimensions = {
      {100, 100}, {1000, 1000}, {10000, 10000}, {10000, 50000}, {50000, 50000}};

  for (const auto& dim : dimensions) {
    int m = dim.first;
    int n = dim.second;
    int numComponents = static_cast<int>(0.1 * n); // Reducing the components to 90%

    Eigen::MatrixXd dataset = generateRandomDataset(m, n);

    auto start = std::chrono::high_resolution_clock::now(); // Start measuring the time elapsed
    Eigen::MatrixXd projectedData = performPCA(dataset, numComponents);
    auto end = std::chrono::high_resolution_clock::now();  // End measuring the time elapsed

    std::cout << "Dataset Dimensions (" << m << ", " << n << ") PCA resultant Dimensions: (" << projectedData.rows() << ", " << projectedData.cols() << ")\n";
    std::cout << "Elapsed time in ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
  }

  return 0;
}
