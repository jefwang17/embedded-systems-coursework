#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>
#include <limits>

using namespace std;

// ----- Templated 2D vector class -----
template <typename T>
struct Vec2 {
    T x, y;

    Vec2(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}
};

// vector + vector
template <typename T>
Vec2<T> operator+(const Vec2<T>& a, const Vec2<T>& b) {
    return Vec2<T>(a.x + b.x, a.y + b.y);
}

// vector - vector
template <typename T>
Vec2<T> operator-(const Vec2<T>& a, const Vec2<T>& b) {
    return Vec2<T>(a.x - b.x, a.y - b.y);
}

// unary - (negate vector)
template <typename T>
Vec2<T> operator-(const Vec2<T>& v) {
    return Vec2<T>(-v.x, -v.y);
}

// vector * scalar
template <typename T>
Vec2<T> operator*(const Vec2<T>& v, T s) {
    return Vec2<T>(v.x * s, v.y * s);
}

// scalar * vector
template <typename T>
Vec2<T> operator*(T s, const Vec2<T>& v) {
    return v * s;
}

// vector * vector  (dot product)
template <typename T>
T operator*(const Vec2<T>& a, const Vec2<T>& b) {
    return a.x * b.x + a.y * b.y;
}

// ----- Expression value: scalar OR vector -----
using Num = long long;  // you can change to double if you prefer

struct Value {
    bool isVector;
    Vec2<Num> v;
    Num s;

    static Value makeVector(const Vec2<Num>& vec) {
        Value r;
        r.isVector = true;
        r.v = vec;
        r.s = 0;
        return r;
    }
    static Value makeScalar(Num scalar) {
        Value r;
        r.isVector = false;
        r.s = scalar;
        r.v = Vec2<Num>();
        return r;
    }
};

// ----- Globals for parser -----
string expr;
size_t posIdx = 0;
unordered_map<string, Vec2<Num>> table;

// Forward declarations
Value parseExpression();
Value parseTerm();
Value parseFactor();
Value parsePrimary();

void skipSpaces() {
    while (posIdx < expr.size() && isspace(static_cast<unsigned char>(expr[posIdx])))
        ++posIdx;
}

// expression = term { ('+' | '-') term }
Value parseExpression() {
    Value left = parseTerm();
    while (true) {
        skipSpaces();
        if (posIdx >= expr.size()) break;
        char op = expr[posIdx];
        if (op != '+' && op != '-') break;
        ++posIdx;  // consume op
        Value right = parseTerm();

        if (op == '+') {
            if (left.isVector && right.isVector)
                left = Value::makeVector(left.v + right.v);
            else
                left = Value::makeScalar(left.s + right.s); // scalar + scalar (just in case)
        } else { // '-'
            if (left.isVector && right.isVector)
                left = Value::makeVector(left.v - right.v);
            else
                left = Value::makeScalar(left.s - right.s);
        }
    }
    return left;
}

// term = factor { '*' factor }
Value parseTerm() {
    Value left = parseFactor();
    while (true) {
        skipSpaces();
        if (posIdx >= expr.size() || expr[posIdx] != '*') break;
        ++posIdx;  // consume '*'
        Value right = parseFactor();

        if (left.isVector && right.isVector) {
            // dot product -> scalar
            Num dp = left.v * right.v;
            left = Value::makeScalar(dp);
        } else if (left.isVector && !right.isVector) {
            left = Value::makeVector(left.v * right.s);
        } else if (!left.isVector && right.isVector) {
            left = Value::makeVector(left.s * right.v);
        } else { // scalar * scalar (just in case)
            left = Value::makeScalar(left.s * right.s);
        }
    }
    return left;
}

// factor = '-' factor | primary
Value parseFactor() {
    skipSpaces();
    if (posIdx < expr.size() && expr[posIdx] == '-') {
        ++posIdx;  // consume unary '-'
        Value inner = parseFactor();
        if (inner.isVector)
            inner.v = -inner.v;
        else
            inner.s = -inner.s;
        return inner;
    }
    return parsePrimary();
}

// primary = number | identifier | '(' expression ')'
Value parsePrimary() {
    skipSpaces();
    if (posIdx >= expr.size()) return Value::makeScalar(0);

    char c = expr[posIdx];

    // Parenthesized expression
    if (c == '(') {
        ++posIdx;  // consume '('
        Value val = parseExpression();
        skipSpaces();
        if (posIdx < expr.size() && expr[posIdx] == ')')
            ++posIdx;
        return val;
    }

    // Number (scalar constant)
    if (isdigit(static_cast<unsigned char>(c))) {
        Num val = 0;
        while (posIdx < expr.size() &&
               isdigit(static_cast<unsigned char>(expr[posIdx]))) {
            val = val * 10 + (expr[posIdx] - '0');
            ++posIdx;
        }
        return Value::makeScalar(val);
    }

    // Identifier (vector variable name)
    if (isalpha(static_cast<unsigned char>(c)) || c == '_') {
        string name;
        while (posIdx < expr.size() &&
               (isalnum(static_cast<unsigned char>(expr[posIdx])) ||
                expr[posIdx] == '_')) {
            name.push_back(expr[posIdx]);
            ++posIdx;
        }
        auto it = table.find(name);
        if (it != table.end()) {
            return Value::makeVector(it->second);
        } else {
            // Shouldn't happen if input is valid; treat as scalar 0
            return Value::makeScalar(0);
        }
    }

    // Fallback (should not be reached with valid input)
    ++posIdx;
    return Value::makeScalar(0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    // Read N vector definitions: name = (x,y)
    for (int i = 0; i < N; ++i) {
        string name;
        char eq, lp, comma, rp;
        Num x, y;

        cin >> name;     // e.g., v1
        cin >> eq;       // '='
        cin >> lp;       // '('
        cin >> x;        // x
        cin >> comma;    // ','
        cin >> y;        // y
        cin >> rp;       // ')'

        table[name] = Vec2<Num>(x, y);
    }

    // Consume end of line after last vector definition
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Read the expression line (may contain spaces)
    getline(cin, expr);
    posIdx = 0;

    Value result = parseExpression();

    if (result.isVector) {
        cout << "(" << result.v.x << "," << result.v.y << ")\n";
    } else {
        cout << result.s << "\n";
    }

    return 0;
}
