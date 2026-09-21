#include <iostream>
#include <vector>
using namespace std;

// Linked list node
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Reverse k nodes starting from head
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* node = head;
    int count = 0;

    // Check if we have at least k nodes
    while (node != nullptr && count < k) {
        node = node->next;
        count++;
    }
    if (count < k) return head; // Not enough nodes → no change

    // Reverse k nodes
    ListNode* prev = nullptr;
    ListNode* curr = head;
    ListNode* next = nullptr;
    count = 0;

    while (curr != nullptr && count < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }

    // Recursively handle the rest
    if (next != nullptr) {
        head->next = reverseKGroup(next, k);
    }

    return prev; // New head of this block
}

// Helper to print list
void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val;
        if (head->next != nullptr) cout << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    int n, k;

    // ---- INPUT SECTION ----
    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter the list values: ";
    vector<int> vals(n);
    for (int i = 0; i < n; i++) cin >> vals[i];

    cout << "Enter k: ";
    cin >> k;

    // ---- BUILD LINKED LIST ----
    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    for (int x : vals) {
        ListNode* node = new ListNode(x);
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    // ---- PROCESS ----
    head = reverseKGroup(head, k);

    // ---- OUTPUT ----
    cout << "Modified list: ";
    printList(head);

    return 0;
}
