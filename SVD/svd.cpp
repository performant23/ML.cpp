#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <random>
#include <chrono>

// Generate random dataset
Eigen::MatrixXd generateRandomDataset(int m, int n) {
    std::random_device rd;
    std::mt19937 rand_gen(rd());
    std::uniform_real_distribution<> d(0, 1);
    Eigen::MatrixXd dataset(m, n);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            dataset(i, j) = d(rand_gen);
        }
    }

    return dataset;
}

void performSVD(const Eigen::MatrixXd& dataset, Eigen::MatrixXd& U, Eigen::VectorXd& singularValues, Eigen::MatrixXd& V) {
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(dataset, Eigen::ComputeThinU | Eigen::ComputeThinV);
    U = svd.matrixU();
    singularValues = svd.singularValues();
    V = svd.matrixV();
}

int main() {
    std::vector<std::pair<int, int>> dimensions = {{2,2}, {5,5}, {10,10}, {50,50}, {100, 100}, {500,500}, {1000, 1000}};

    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open output file.\n";
        return 1;
    }

    for (const auto& dim : dimensions) {
        int m = dim.first;
        int n = dim.second;
        Eigen::MatrixXd dataset = generateRandomDataset(m, n);

        auto start = std::chrono::high_resolution_clock::now();

        Eigen::MatrixXd U, V;
        Eigen::VectorXd singularValues;
        performSVD(dataset, U, singularValues, V);

        auto end = std::chrono::high_resolution_clock::now();

        std::cout << "SVD completed for dataset of dimensions (" << m << ", " << n << ")\n";
        std::cout << "Elapsed time in seconds: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " seconds\n";
        outputFile << "U:\n" << U << std::endl;
        outputFile << "Singular Values:\n" << singularValues << std::endl;
        outputFile << "V:\n" << V << std::endl;
        outputFile << "-------------------------------------------------------------------------------------------";
        outputFile << "\n\n\n\n";
    }

    outputFile.close();

    return 0;
}
