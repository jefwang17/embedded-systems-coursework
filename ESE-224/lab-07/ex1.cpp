#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

struct Node {
    int val;
    Node* next;
    explicit Node(int v) : val(v), next(nullptr) {}
};

Node* buildList(const vector<int>& vals) {
    Node* head = nullptr, *tail = nullptr;
    for (int v : vals) {
        Node* cur = new Node(v);
        if (!head) head = tail = cur;
        else { tail->next = cur; tail = cur; }
    }
    return head;
}

static int getNext(Node*& p) {
    if (!p) return -1;
    int v = p->val; p = p->next; return v;
}

vector<vector<int> > spiralMatrix(int m, int n, Node* head) {
    vector<vector<int> > a(m, vector<int>(n, -1));
    int top = 0, bottom = m - 1, left = 0, right = n - 1;
    Node* p = head;

    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; ++j) a[top][j] = getNext(p);
        ++top;

        for (int i = top; i <= bottom; ++i) a[i][right] = getNext(p);
        --right;

        if (top <= bottom) {
            for (int j = right; j >= left; --j) a[bottom][j] = getNext(p);
            --bottom;
        }
        if (left <= right) {
            for (int i = bottom; i >= top; --i) a[i][left] = getNext(p);
            ++left;
        }
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cout << "Enter matrix dimensions (m n): " << flush;
    if (!(cin >> m >> n)) return 0;
    cout << "Enter linked list values separated by spaces:\n" << flush;
    string dummy; getline(cin, dummy); // consume EOL
    string line; getline(cin, line);

    // parse values
    istringstream iss(line);
    vector<int> vals; int x;
    while (iss >> x) vals.push_back(x);

    cout << "\n[INFO] Generating a " << m << " x " << n << " matrix in spiral order...\n\n";

    Node* head = buildList(vals);
    vector<vector<int> > mat = spiralMatrix(m, n, head);

    cout << "[OUTPUT] Generated Matrix:\n";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j) cout << ' ';
            cout << mat[i][j];
        }
        cout << "\n";
    }

    // free list
    while (head) { Node* t = head->next; delete head; head = t; }
    return 0;
}
