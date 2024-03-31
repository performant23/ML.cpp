#include <iostream>
#include <Eigen/Dense>
#include <chrono>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace Eigen;
using namespace std;
using namespace std::chrono;

// Non-negative Matrix Factorization (NMF)
void nmf(const MatrixXd& V, int rank, MatrixXd& W, MatrixXd& H, int max_iter = 100, double tol = 1e-6) {
    int m = V.rows();
    int n = V.cols();

    W = MatrixXd::Random(m, rank).cwiseAbs();
    H = MatrixXd::Random(rank, n).cwiseAbs();

    for (int iter = 0; iter < max_iter; ++iter) {
        MatrixXd W_update = W.array() * ((V * H.transpose()).array() / (W * H * H.transpose()).array());
        W = W_update.cwiseMax(1e-16);

        MatrixXd H_update = H.array() * ((W.transpose() * V).array() / (W.transpose() * W * H).array());
        H = H_update.cwiseMax(1e-16);

        double error = (V - W * H).norm();

        if (error < tol) {
            cout << "Converged after " << iter + 1 << " iterations." << endl;
            break;
        }
    }
}

int main() {
    vector<pair<int, int>> dimensions = {{2, 2}, {5, 5}, {10, 10}, {50, 50}, {100, 100}, {500, 500}, {1000, 1000}};
    int rank = 2;
    ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }

    for (const auto& dim : dimensions) {
        int rows = dim.first;
        int cols = dim.second;
        MatrixXd V = MatrixXd::Random(rows, cols).cwiseAbs();
        auto start = high_resolution_clock::now();
        MatrixXd W, H;
        nmf(V, rank, W, H);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start).count();
        double durationSeconds = static_cast<double>(duration) / 1000000000.0;

        cout << "Elapsed time for dataset of dimensions (" << rows << "x" << cols << "): " << std::fixed << std::setprecision(9) << durationSeconds << " seconds" << endl;

        outputFile << "Dataset dimensions (" << rows << "x" << cols << "):" << endl;
        outputFile << "Matrix W:" << endl << W << endl;
        outputFile << "Matrix H:" << endl << H << endl;
        outputFile << "----------------------------------------------------" << endl;
    }

    outputFile.close();
    return 0;
}