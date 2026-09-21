#include <iostream>
using namespace std;

int main() {
    // Step 1: Get user input
    int n;
    cout << "Enter a non-negative integer: ";
    cin >> n;

    // Step 2: Validate input
    if (n < 0) {
        cout << "Error: Factorial is not defined for negative numbers." << endl;
        return 1; // exit program early
    }

    // Step 3: Calculate factorial
    long long fact = 1; // use long long to handle larger values
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }

    // Step 4: Print result
    cout << n << "! = " << fact << endl;

    return 0;
}
