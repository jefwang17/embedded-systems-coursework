#include "Banking.h"
#include <iostream>
using namespace std;

// ----- Account impl -----
Account::Account(const string& name, int start) : owner(name), balance(start) {}

string Account::getOwner() const   { return owner; }
int    Account::getBalance() const { return balance; }
int&   Account::accessBalance()    { return balance; }

// ----- Free functions -----

// Call-by-VALUE: works on a copy; Account remains unchanged.
void depositByValue(int balance, int amount) {
    balance = balance + amount;
    cout << "[depositByValue] New (copy) balance = " << balance
         << "  (original not changed)\n";
}

// Call-by-REFERENCE: modifies the caller's actual balance.
void depositByReference(int& balance, int amount) {
    balance = balance + amount;
    cout << "[depositByReference] Applied. Current balance = " << balance << "\n";
}

// Const reference printer: no copy, no modification.
void printBalance(const int& balance, const string& label) {
    cout << label << balance << "\n";
}