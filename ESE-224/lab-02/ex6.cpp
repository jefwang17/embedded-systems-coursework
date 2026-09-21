#include <iostream>
using namespace std;

int main() {
    long long num;
    cout << "Enter a non-negative integer: ";
    cin >> num;

    if (num < 0) {
        cout << "Error: input must be non-negative." << endl;
        return 1;
    }

    // While num has more than one digit
    while (num >= 10) {
        long long tempSum = 0;

        // Add digits of num
        while (num > 0) {
            tempSum += num % 10;  // extract last digit
            num /= 10;            // drop last digit
        }

        // Replace num with the sum of its digits
        num = tempSum;
    }

    cout << "Single-digit result: " << num << endl;
    return 0;
}
