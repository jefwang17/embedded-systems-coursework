#include <iostream>
using namespace std;

int main() {
    // Step 1: Get user input
    int n;
    cout << "Enter a positive integer: ";
    cin >> n;

    // Step 2: Initialize sum
    int sum = 0;

    // Step 3: Iterate using for loop
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0) {
            sum += i;
        }
    }

    // Step 4: Print result
    cout << "Sum = " << sum << endl;

    return 0;
}
