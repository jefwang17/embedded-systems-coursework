#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string expr;
int idx = 0;

// Forward declaration
uint8_t parseExpr();

// Skip whitespace (safe)
void skip() {
    while (idx < expr.size() && isspace(expr[idx])) idx++;
}

// Parse literal: bXXXXXXXX
uint8_t parseLiteral() {
    skip();
    idx++; // skip the 'b'
    uint8_t val = 0;

    for (int i = 0; i < 8; i++) {
        val <<= 1;
        if (expr[idx] == '1') val |= 1;
        idx++;
    }
    return val;
}

// Parse NOT: !(subExpr)
uint8_t parseNot() {
    skip();
    idx++; // skip '!'

    skip();
    idx++; // skip '('

    uint8_t v = parseExpr();

    skip();
    idx++; // skip ')'

    return ~v; // bitwise NOT
}

// Parse &(expr1,expr2,...)
uint8_t parseAnd() {
    skip();
    idx++; // skip '&'

    skip();
    idx++; // skip '('

    uint8_t result = 0xFF; // all 1’s for AND identity

    while (true) {
        uint8_t v = parseExpr();
        result &= v;

        skip();
        if (expr[idx] == ')') {
            idx++; // skip ')'
            break;
        }
        idx++; // skip ','
    }

    return result;
}

// Parse |(expr1,expr2,...)
uint8_t parseOr() {
    skip();
    idx++; // skip '|'

    skip();
    idx++; // skip '('

    uint8_t result = 0x00; // all 0’s for OR identity

    while (true) {
        uint8_t v = parseExpr();
        result |= v;

        skip();
        if (expr[idx] == ')') {
            idx++;
            break;
        }
        idx++; // skip ','
    }

    return result;
}

// Recursive dispatcher
uint8_t parseExpr() {
    skip();
    char c = expr[idx];

    if (c == 'b') return parseLiteral();
    if (c == '!') return parseNot();
    if (c == '&') return parseAnd();
    if (c == '|') return parseOr();

    return 0; // safety
}

// Converts 8-bit number to binary string
string toBinary(uint8_t v) {
    string s = "";
    for (int i = 7; i >= 0; i--)
        s += ((v >> i) & 1) ? '1' : '0';
    return s;
}

int main() {
    getline(cin, expr);
    uint8_t value = parseExpr();
    cout << toBinary(value) << endl;
    return 0;
}
