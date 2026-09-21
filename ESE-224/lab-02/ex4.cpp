#include <iostream>
using namespace std;

int main() {
    int choice;
    double num1, num2;

    // Infinite loop
    for (;;) {
        // Display menu
        cout << "\n===== Simple Calculator =====" << endl;
        cout << "1. Add" << endl;
        cout << "2. Subtract" << endl;
        cout << "3. Multiply" << endl;
        cout << "4. Divide" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // Addition
                cout << "Enter two numbers: ";
                cin >> num1 >> num2;
                cout << "Result: " << (num1 + num2) << endl;
                break;

            case 2: // Subtraction
                cout << "Enter two numbers: ";
                cin >> num1 >> num2;
                cout << "Result: " << (num1 - num2) << endl;
                break;

            case 3: // Multiplication
                cout << "Enter two numbers: ";
                cin >> num1 >> num2;
                cout << "Result: " << (num1 * num2) << endl;
                break;

            case 4: // Division
                cout << "Enter two numbers: ";
                cin >> num1 >> num2;
                if (num2 != 0)
                    cout << "Result: " << (num1 / num2) << endl;
                else
                    cout << "Error: Division by zero is not allowed." << endl;
                break;

            case 5: // Exit
                cout << "Exiting calculator..." << endl;
                return 0; // end program

            default: // Invalid input
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
