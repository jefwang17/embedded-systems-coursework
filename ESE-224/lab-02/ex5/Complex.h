#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    // Constructors
    Complex();
    Complex(double r, double i);

    // Arithmetic operators
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;

    // Utilities
    double amplitude() const;       // modulus
    void display() const;           // prints (a ± bi) with two decimals

    // Menu runner (encapsulates the program logic)
    static void runCalculator();

private:
    // Helpers for menu I/O
    static Complex readComplex(const std::string& prompt);
    static void printMenu();
};

#endif // COMPLEX_H
