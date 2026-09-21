#include <iostream>
#include <iomanip>
using namespace std;

constexpr int M = 3;  // rows
constexpr int N = 3;  // cols

void readMatrix(int A[M][N], const char* name) {
    cout << "Enter " << M*N << " integers for " << name << " (" << M << "x" << N << ") row by row:\n";
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            cin >> A[i][j];
}

void printMatrix(const int A[M][N], const char* title) {
    cout << "\n" << title << " (" << M << "x" << N << "):\n";
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j)
            cout << setw(6) << A[i][j];
        cout << '\n';
    }
}

void addMatrix(const int A[M][N], const int B[M][N], int C[M][N]) {
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            C[i][j] = A[i][j] + B[i][j];
}

void transposeMatrix(const int A[M][N], int T[N][M]) {
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            T[j][i] = A[i][j];
}

void scaleInPlace(int A[M][N], int k) {
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            A[i][j] *= k;
}

int main() {

    int A[M][N], B[M][N];
    cout << "Read two positive-integer matrices A and B.\n";
    readMatrix(A, "A");
    readMatrix(B, "B");

    for (;;) {
        cout << "\nChoose an operation:\n"
             << "  1) Addition  (C = A + B)\n"
             << "  2) Transpose (T = A^T)\n"
             << "  3) Scale     (A = k * A)\n"
             << "  4) Exit\n"
             << "Enter choice: ";

        int choice;
        if (!(cin >> choice)) return 0;

        if (choice == 1) {
            int C[M][N];
            addMatrix(A, B, C);
            printMatrix(A, "Matrix A");
            printMatrix(B, "Matrix B");
            printMatrix(C, "C = A + B");
        } else if (choice == 2) {
            int T[N][M];
            transposeMatrix(A, T);
            printMatrix(A, "Matrix A");
            // Print transpose with correct dimensions N x M
            cout << "\nTranspose of A (" << N << "x" << M << "):\n";
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j)
                    cout << setw(6) << T[i][j];
                cout << '\n';
            }
        } else if (choice == 3) {
            cout << "Enter integer scalar k: ";
            int k; cin >> k;
            scaleInPlace(A, k);
            printMatrix(A, "A (after scaling)");
        } else if (choice == 4) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice. Try 1–4.\n";
        }
    }
    return 0;
}
