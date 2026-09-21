#include "LibraryMember.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Constructors
LibraryMember::LibraryMember()
    : memberID(""), name(""), borrowedBooks(0), maxBooks(5) {
}

LibraryMember::LibraryMember(const string& id, const string& nm, int maxAllowed)
    : memberID(id), name(nm), borrowedBooks(0), maxBooks(maxAllowed > 0 ? maxAllowed : 5) {
}

// Getters
string LibraryMember::getMemberID() const { return memberID; }
string LibraryMember::getName()     const { return name; }
int    LibraryMember::getBorrowed() const { return borrowedBooks; }
int    LibraryMember::getMaxBooks() const { return maxBooks; }

// Actions
bool LibraryMember::borrowBook(int count) {
    if (count <= 0) {
        cout << "Error: borrow count must be positive.\n";
        return false;
    }
    if (borrowedBooks + count > maxBooks) {
        cout << "Error: borrowing " << count
            << " exceeds limit (current " << borrowedBooks
            << ", max " << maxBooks << ").\n";
        return false;
    }
    borrowedBooks += count;
    return true;
}

bool LibraryMember::returnBook(int count) {
    if (count <= 0) {
        cout << "Error: return count must be positive.\n";
        return false;
    }
    if (count > borrowedBooks) {
        cout << "Error: cannot return " << count
            << " - only " << borrowedBooks << " borrowed.\n";
        return false;
    }
    borrowedBooks -= count;
    return true;
}

// Display
void LibraryMember::displayInfo() const {
    cout << left;
    cout << "Member ID : " << memberID << "\n"
        << "Name      : " << name << "\n"
        << "Borrowed  : " << borrowedBooks << "\n"
        << "Max Limit : " << maxBooks << "\n"
        << "-----------------------------\n";
}
