#include "Complex.h"
#include <cmath>
#include <iomanip>
#include <limits>
using namespace std;

// ---- Constructors ----
Complex::Complex() : real(0.0), imag(0.0) {}
Complex::Complex(double r, double i) : real(r), imag(i) {}

// ---- Operator Overloads ----
Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex& other) const {
    // (a + bi)(c + di) = (ac - bd) + (ad + bc)i
    double a = real, b = imag;
    double c = other.real, d = other.imag;
    return Complex(a*c - b*d, a*d + b*c);
}

// ---- Utilities ----
double Complex::amplitude() const {
    return std::sqrt(real*real + imag*imag);
}

void Complex::display() const {
    cout << fixed << setprecision(2);
    cout << "(" << real << (imag < 0 ? " - " : " + ") << std::fabs(imag) << "i)";
}

// ---- Menu helpers ----
void Complex::printMenu() {
    cout << "\n===== Complex Number Calculator =====\n"
         << "1. Add two complex numbers\n"
         << "2. Subtract two complex numbers\n"
         << "3. Multiply two complex numbers\n"
         << "4. Calculate amplitude (modulus)\n"
         << "5. Exit\n"
         << "Enter your choice: ";
}

Complex Complex::readComplex(const std::string& prompt) {
    while (true) {
        cout << prompt << "\n";
        cout << "  Enter real part: ";
        double r, i;
        if (!(cin >> r)) {
            cout << "  Invalid input. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cout << "  Enter imaginary part: ";
        if (!(cin >> i)) {
            cout << "  Invalid input. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        return Complex(r, i);
    }
}

// ---- Menu runner ----
void Complex::runCalculator() {
    int choice;
    do {
        printMenu();
        if (!(cin >> choice)) {
            cout << "Invalid choice. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                Complex a = readComplex("Enter the FIRST complex number:");
                Complex b = readComplex("Enter the SECOND complex number:");
                Complex c = a + b;
                cout << "Result: ";
                c.display();
                cout << "\n";
                break;
            }
            case 2: {
                Complex a = readComplex("Enter the FIRST complex number:");
                Complex b = readComplex("Enter the SECOND complex number:");
                Complex c = a - b;
                cout << "Result: ";
                c.display();
                cout << "\n";
                break;
            }
            case 3: {
                Complex a = readComplex("Enter the FIRST complex number:");
                Complex b = readComplex("Enter the SECOND complex number:");
                Complex c = a * b;
                cout << "Result: ";
                c.display();
                cout << "\n";
                break;
            }
            case 4: {
                Complex a = readComplex("Enter the complex number:");
                cout << fixed << setprecision(4);
                cout << "Amplitude: " << a.amplitude() << "\n";
                break;
            }
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please select 1-5.\n";
        }

    } while (choice != 5);
}
