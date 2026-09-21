#include <iostream>

using namespace std;

int main() {
    //step 1: Get number of terms
    int terms;
    cout << "Enter number of terms: ";
    cin >> terms;

    // step 2: Initialize first two values
    long long a = 0, b = 1;
    
    // step3: Loop through terms
    for (int i = 0; i < terms; i++) {
        long long next = a + b; // calculate next term
        a = b;                  // update a
        b = next;               // update b
        if (i == 0) cout << "0 ";
        cout << a << " ";  
    }

    cout << endl;
    return 0;
}