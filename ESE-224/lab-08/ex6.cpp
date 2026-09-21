#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};

vector<int> nextLargerNodes(ListNode* head) {
    vector<int> values;
    for (ListNode* cur = head; cur != nullptr; cur = cur->next)
        values.push_back(cur->val);

    int n = values.size();
    vector<int> ans(n, 0);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && values[i] > values[st.top()]) {
            ans[st.top()] = values[i];
            st.pop();
        }
        st.push(i);
    }
    return ans;
}

int main() {
    int n;
    cin >> n;

    if (n <= 0) return 0;

    // Build linked list from input
    int x;
    cin >> x;
    ListNode* head = new ListNode(x);
    ListNode* curr = head;

    for (int i = 1; i < n; i++) {
        cin >> x;
        curr->next = new ListNode(x);
        curr = curr->next;
    }

    // Compute next greater nodes
    vector<int> result = nextLargerNodes(head);

    // Output result
    for (int i = 0; i < n; i++) {
        cout << result[i];
        if (i != n - 1) cout << " ";
    }
    cout << "\n";

    return 0;
}
