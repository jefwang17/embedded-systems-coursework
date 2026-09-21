#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// Function to build an m x n matrix filled 1..m*n
vector<vector<int>> buildMatrix(int m, int n) {
    vector<vector<int>> mat(m, vector<int>(n));
    int val = 1;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            mat[i][j] = val++;
    return mat;
}

// Function to traverse matrix in spiral order
vector<int> spiralOrder(const vector<vector<int>>& mat) {
    int m = (int)mat.size();
    int n = (int)mat[0].size();
    vector<int> out;

    int top = 0, bottom = m - 1, left = 0, right = n - 1;
    while (top <= bottom && left <= right) {
        // top row
        for (int j = left; j <= right; ++j)
            out.push_back(mat[top][j]);
        ++top;

        // right column
        for (int i = top; i <= bottom; ++i)
            out.push_back(mat[i][right]);
        --right;

        // bottom row (if any)
        if (top <= bottom) {
            for (int j = right; j >= left; --j)
                out.push_back(mat[bottom][j]);
            --bottom;
        }

        // left column (if any)
        if (left <= right) {
            for (int i = bottom; i >= top; --i)
                out.push_back(mat[i][left]);
            ++left;
        }
    }
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;

    // Clear and user-friendly prompt
    cout << "Read two positive integers m (rows) and n (columns)." << endl;
    cout << "For example, to make a 3x4 matrix, type: 3 4" << endl;
    cout << "Enter m and n: ";
    cin >> m >> n;

    if (m <= 0 || n <= 0) {
        cerr << "Error: both m and n must be positive integers.\n";
        return 1;
    }

    auto mat = buildMatrix(m, n);
    auto spiral = spiralOrder(mat);

    cout << "\nMatrix (" << m << "x" << n << "):\n";
    for (const auto& row : mat) {
        for (int x : row)
            cout << setw(6) << x;
        cout << '\n';
    }

    cout << "\nSpiral order:\n";
    for (size_t i = 0; i < spiral.size(); ++i) {
        if (i) cout << ' ';
        cout << spiral[i];
    }
    cout << '\n';

    return 0;
}
