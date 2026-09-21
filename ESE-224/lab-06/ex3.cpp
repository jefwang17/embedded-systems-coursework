#include <iostream>
#include <vector>
using namespace std;

// boundary-sum function per lab requirement
int boundarySum(const vector<vector<int>>& matrix, int m, int n) {
    int sum = 0;

    if (m == 1) {
        // Only one row — all elements are boundary
        for (int j = 0; j < n; ++j)
            sum += matrix[0][j];
        return sum;
    }
    if (n == 1) {
        // Only one column — all elements are boundary
        for (int i = 0; i < m; ++i)
            sum += matrix[i][0];
        return sum;
    }

    // Top and bottom rows
    for (int j = 0; j < n; ++j) {
        sum += matrix[0][j];       // top row
        sum += matrix[m - 1][j];   // bottom row
    }

    // Left and right columns of middle rows
    for (int i = 1; i < m - 1; ++i) {
        sum += matrix[i][0];       // left boundary
        sum += matrix[i][n - 1];   // right boundary
    }

    return sum;
}

int main() {
    int m, n;
    cout << "Read m (rows) and n (columns). Example: 3 4\n";
    cout << "Enter m and n: ";
    cin >> m >> n;

    if (m <= 0 || n <= 0) {
        cerr << "Error: m and n must be positive integers.\n";
        return 1;
    }

    vector<vector<int>> matrix(m, vector<int>(n));
    cout << "Enter " << (m * n) << " integers row by row:\n";
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> matrix[i][j];

    int result = boundarySum(matrix, m, n);
    cout << "Boundary sum = " << result << "\n";

    return 0;
}
