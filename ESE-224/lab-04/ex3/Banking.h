#ifndef BANKING_H
#define BANKING_H

#include <string>
using namespace std;

class Account {
private:
    string owner;
    int balance;

public:
    Account(const string& name, int start);

    string getOwner() const;
    int    getBalance() const;

    // Helper to safely get a writable reference for the reference demo
    int&   accessBalance();   // returns reference to the internal balance
};

// ---- Function Prototypes (free functions) ----
void depositByValue(int balance, int amount);        // copy (does NOT change Account)
void depositByReference(int& balance, int amount);   // reference (DOES change Account)
void printBalance(const int& balance, const string& label); // const ref (read-only)

#endif
