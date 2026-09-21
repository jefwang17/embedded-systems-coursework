#include "book.h"
#include <iostream>
using namespace std;

// g++ main.cpp book.cpp -o main

int main() {
    // Create Book using parameterized constructor
    Book b1("The Pragmatic Programmer", "Andrew Hunt", "978-0201616224", 45.00);

    // Create Book using default constructor and setters
    Book b2;
    b2.setTitle("Clean Code");
    b2.setAuthor("Robert C. Martin");
    b2.setISBN("978-0132350884");
    b2.setPrice(18.50);

    // Display info before discount
    cout << "Before applying discounts:\n";
    b1.displayInfo();
    b2.displayInfo();

    // Apply discount
    b1.applyDiscount(10);  // 10% off
    b2.applyDiscount(20);  // 20% off

    // Display info after discount
    cout << "After applying discounts:\n";
    b1.displayInfo();
    b2.displayInfo();

    return 0;
}
