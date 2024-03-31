#include <iostream>
#include <Eigen/Dense>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace Eigen;
using namespace std;

// Pairwise Euclidean distances
MatrixXd computeDistances(const MatrixXd& X) {
    int n = X.rows();
    MatrixXd D(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            double dist = (X.row(i) - X.row(j)).norm();
            D(i, j) = D(j, i) = dist;
        }
    }
    return D;
}

// Multidimensional Scaling (MDS)
void mds(const MatrixXd& D, int d, MatrixXd& Z) {
    int n = D.rows();

    MatrixXd H = MatrixXd::Identity(n, n) - MatrixXd::Ones(n, n) / n;
    MatrixXd B = -0.5 * H * D * H;

    SelfAdjointEigenSolver<MatrixXd> eigensolver(B);
    MatrixXd eigenvectors = eigensolver.eigenvectors();

    MatrixXd Z_full = eigenvectors.block(0, n - d, n, d);

    MatrixXd S = Z_full.transpose() * D * Z_full;
    SelfAdjointEigenSolver<MatrixXd> eigensolver_S(S);
    MatrixXd Lambda_sqrt_inv = eigensolver_S.eigenvectors().real().cwiseSqrt().inverse();
    Z = Z_full * Lambda_sqrt_inv;
}

int main() {
    ofstream output_file("output.txt");
    vector<int> dimensions = {2, 5, 10, 50, 100, 500, 1000};
    for (int dim : dimensions) {
        MatrixXd X = MatrixXd::Random(dim, 3);
        MatrixXd D = computeDistances(X);
        int d = 2;

        auto start = chrono::high_resolution_clock::now();
        MatrixXd Z;
        mds(D, d, Z);
        auto finish = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = finish - start;

        cout << "Dimensions: " << dim << "\n";
        cout << "Execution time: " << std::fixed << std::setprecision(9) << elapsed.count() << " seconds \n";

        output_file << "Embedded Data Matrix Z (" << dim << "x" << dim << "):\n" << Z << "\n\n";
    }

    output_file.close();
    return 0;
}
