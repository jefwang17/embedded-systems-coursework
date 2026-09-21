#include <iostream>
#include <bitset>
using namespace std;

class BitMask {
private:
    unsigned int value;

public:
    // Constructor
    BitMask(unsigned int v = 0) : value(v) {}

    // Display helper
    void print(const string& label) const {
        cout << label << " = " << value 
             << "  (" << bitset<8>(value) << ")" << endl;
    }

    // Bitwise OR (|)
    BitMask operator|(const BitMask& other) const {
        return BitMask(this->value | other.value);
    }

    // Bitwise AND (&)
    BitMask operator&(const BitMask& other) const {
        return BitMask(this->value & other.value);
    }

    // Bitwise NOT (~)
    BitMask operator~() const {
        return BitMask(~this->value);
    }
};

int main() {
    BitMask a(0b00001010);  // 10
    BitMask b(0b00001100);  // 12

    cout << "BitMask Demonstration\n\n";

    a.print("a");
    b.print("b");

    BitMask result_or  = a | b;
    BitMask result_and = a & b;
    BitMask result_not = ~a;

    cout << "\nResults:\n";
    result_or.print("a | b");
    result_and.print("a & b");
    result_not.print("~a");

    return 0;
}
