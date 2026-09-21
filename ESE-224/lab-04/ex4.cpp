// ESE 224 - Lab 4, Exercise 4
// Menu-Driven GCD (call-by-value) and Swap (call-by-reference)

#include <iostream>
#include <string>
#include <cstdlib>  // rand, srand
#include <ctime>    // time
using namespace std;

// -------- Function Prototypes --------
void printMenu(int A, int B);
int  promptChoice();
int  readPositiveInt(const string& label);

int  findGCD(int x, int y);            // call-by-value
void swapState(int& p_A, int& p_B);    // call-by-reference

void actionSetValues(int& A, int& B);
void actionComputeGCD(const int A, const int B);
void actionSwapValues(int& A, int& B);
void actionRandomizeValues(int& A, int& B, int lo, int hi);
void actionExplainModes();
void actionShowState(const int A, const int B);

int  nextInt(int minIncl, int maxIncl);   // simple RNG

// -------------- MAIN -----------------
int main() {
    srand(time(0)); // seed RNG once

    int A = 24;
    int B = 18;
    bool running = true;

    while (running) {
        printMenu(A, B);
        int choice = promptChoice();

        switch (choice) {
            case 1: actionSetValues(A, B); break;
            case 2: actionComputeGCD(A, B); break;
            case 3: actionSwapValues(A, B); break;
            case 4: actionExplainModes(); break;
            case 5: actionRandomizeValues(A, B, 1, 100); break;
            case 6: actionShowState(A, B); break;
            case 7: cout << "Goodbye!\n"; running = false; break;
            default: cout << "Invalid choice.\n"; break;
        }

        if (running) {
            cout << "\nPress Enter to continue...";
            cin.ignore(10000, '\n'); // clear any leftover input
            cin.get();               // wait for Enter
        }
    }
    return 0;
}

// -------- Function Definitions --------
void printMenu(int A, int B) {
    cout << "\n===== Menu: GCD & Swap Demo =====\n";
    cout << "Current A = " << A << ", B = " << B << "\n";
    cout << "1) Set values of A and B\n";
    cout << "2) Compute GCD(A, B) [call-by-value]\n";
    cout << "3) Swap A and B [call-by-reference]\n";
    cout << "4) Explain call-by-value vs call-by-reference\n";
    cout << "5) Randomize A and B in [1..100]\n";
    cout << "6) Show current state\n";
    cout << "7) Exit\n";
    cout << "Select: ";
}

int promptChoice() {
    int c;
    if (!(cin >> c)) {
        cin.clear();
        cin.ignore(10000, '\n'); // discard bad input
        return -1;
    }
    return c;
}

int readPositiveInt(const string& label) {
    int v;
    while (true) {
        cout << "Enter " << label << " (positive integer): ";
        if (cin >> v && v > 0) return v;
        cout << "Invalid. Try again.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

// Euclidean GCD (call-by-value)
int findGCD(int x, int y) {
    while (y != 0) {
        int r = x % y;
        x = y;
        y = r;
    }
    return (x < 0) ? -x : x;
}

// Swap (call-by-reference)
void swapState(int& p_A, int& p_B) {
    int temp = p_A;
    p_A = p_B;
    p_B = temp;
}

void actionSetValues(int& A, int& B) {
    A = readPositiveInt("A");
    B = readPositiveInt("B");
    cout << "Set A=" << A << ", B=" << B << "\n";
}

void actionComputeGCD(const int A, const int B) {
    int g = findGCD(A, B);
    cout << "GCD(" << A << ", " << B << ") = " << g << "\n";
    cout << "[Note] A and B remain unchanged because GCD used call-by-value.\n";
}

void actionSwapValues(int& A, int& B) {
    cout << "Before swap: A=" << A << ", B=" << B << "\n";
    swapState(A, B);
    cout << "After swap:  A=" << A << ", B=" << B << "\n";
}

void actionRandomizeValues(int& A, int& B, int lo, int hi) {
    A = nextInt(lo, hi);
    B = nextInt(lo, hi);
    cout << "Randomized: A=" << A << ", B=" << B << "\n";
}

void actionExplainModes() {
    cout << "\n--- Explanation ---\n";
    cout << "Call-by-VALUE: function gets copies of variables; changes don't affect the originals.\n";
    cout << "Call-by-REFERENCE: function gets the actual variables; changes persist in main().\n";
}

void actionShowState(const int A, const int B) {
    cout << "Current values -> A=" << A << ", B=" << B << "\n";
}

int nextInt(int minIncl, int maxIncl) {
    return (rand() % (maxIncl - minIncl + 1)) + minIncl;
}
