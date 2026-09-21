#include "LibraryMember.h"
#include <iostream>
using namespace std;
// g++ main.cpp LibraryMember.cpp -o main
int main() {
    LibraryMember m1("M001", "Alice", 5);

    m1.displayInfo();

    cout << "\nTrying to borrow 3 books:\n";
    m1.borrowBook(3);
    m1.displayInfo();

    cout << "\nTrying to borrow 4 more books:\n";
    m1.borrowBook(4); // Should fail
    m1.displayInfo();

    cout << "\nReturning 2 books:\n";
    m1.returnBook(2);
    m1.displayInfo();

    cout << "\nTrying to return 5 books:\n";
    m1.returnBook(5); // Should fail
    m1.displayInfo();

    return 0;
}

