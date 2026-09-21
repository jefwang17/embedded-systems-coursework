#include <iostream>
#include "Banking.h"
using namespace std;
// g++ main.cpp Banking.cpp -o main

int main() {
    // Create an account
    Account acc("Alice", 100);

    cout << "Owner: " << acc.getOwner() << "\n";
    printBalance(acc.getBalance(), "Initial balance = ");

    // 1) Test Call-by-VALUE (should NOT change the account)
    depositByValue(acc.getBalance(), 50);  // passes a copy
    printBalance(acc.getBalance(), "After depositByValue, balance = ");

    // 2) Test Call-by-REFERENCE (should change the account)
    // We obtain a writable reference from the object for the demo:
    depositByReference(acc.accessBalance(), 50);  // passes actual balance by reference
    printBalance(acc.getBalance(), "After depositByReference, balance = ");

    return 0;
}
