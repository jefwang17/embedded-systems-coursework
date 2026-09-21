#include <iostream>
#include <queue>
#include <string>

using namespace std;

class MyStack {
private:
    queue<int> q1;   // main queue: front() is the top of stack
    queue<int> q2;   // helper queue

public:
    // Push element x to the top of stack.
    void push(int x) {
        // Push into q2, then move everything from q1 to q2, then swap.
        q2.push(x);
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }

    // Remove element currently on top of stack.
    void pop() {
        if (!q1.empty()) {
            q1.pop();
        }
    }

    // Return element on top of stack. (Assume non-empty when called.)
    int top() const {
        if (q1.empty()) return -1;   // sentinel if needed
        return q1.front();
    }

    // Return true if stack is empty.
    bool empty() const {
        return q1.empty();
    }

    // Helper: print from top -> bottom (for SHOW command)
    void print() const {
        cout << "Stack(top->bottom): ";
        if (q1.empty()) {
            cout << "[EMPTY]\n";
            return;
        }
        queue<int> temp = q1;  // copy to traverse without modifying
        bool first = true;
        while (!temp.empty()) {
            if (!first) cout << " -> ";
            first = false;
            cout << "[" << temp.front() << "]";
            temp.pop();
        }
        cout << "\n";
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    MyStack st;
    string cmd;

    while (cin >> cmd) {
        if (cmd == "EXIT") break;

        if (cmd == "PUSH") {
            int x;
            cin >> x;
            cout << "> PUSH " << x << "\n";
            st.push(x);
            cout << "OK PUSH " << x << "\n";
        }
        else if (cmd == "POP") {
            cout << "> POP\n";
            if (!st.empty()) {
                int t = st.top();
                st.pop();
                cout << "POP " << t << "\n";
            } else {
                cout << "POP FAILED (empty)\n";
            }
        }
        else if (cmd == "TOP") {
            cout << "> TOP\n";
            if (!st.empty()) {
                cout << "TOP " << st.top() << "\n";
            } else {
                cout << "TOP FAILED (empty)\n";
            }
        }
        else if (cmd == "SHOW") {
            cout << "> SHOW\n";
            st.print();
        }
        else if (cmd == "EMPTY") {
            cout << "> EMPTY\n";
            cout << (st.empty() ? "true" : "false") << "\n";
        }
        // ignore unknown commands
    }

    return 0;
}
