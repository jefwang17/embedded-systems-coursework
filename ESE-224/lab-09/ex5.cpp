#include <iostream>
#include <bitset>
using namespace std;

struct Node {
    int flags;       // Bit field: bit0=Visible, bit1=Active, bit2=Locked
    Node* next;
    Node* prev;

    Node(int f) : flags(f), next(nullptr), prev(nullptr) {}
};

// Print list forward
void printForward(Node* head) {
    Node* curr = head;
    while (curr) {
        cout << curr->flags << " (" << bitset<3>(curr->flags) << ") -> ";
        curr = curr->next;
    }
    cout << "NULL" << endl;
}

// Print backward from tail
void printBackwardFromTail(Node* tail) {
    Node* curr = tail;
    while (curr) {
        cout << curr->flags << " (" << bitset<3>(curr->flags) << ") -> ";
        curr = curr->prev;
    }
    cout << "NULL" << endl;
}

// Toggle Active bit (bit 1) for every node; no printing here
void toggleActive(Node* head, Node*& tailOut) {
    Node* curr = head;
    Node* tail = nullptr;

    while (curr) {
        curr->flags ^= (1 << 1);   // flip bit 1 (Active)
        tail = curr;               // keep track of tail
        curr = curr->next;
    }

    tailOut = tail;                // return tail pointer to caller
}

int main() {
    // Create nodes with given flags: 3, 4, 1, 6
    Node* n1 = new Node(3); // 011
    Node* n2 = new Node(4); // 100
    Node* n3 = new Node(1); // 001
    Node* n4 = new Node(6); // 110

    // Link nodes (doubly linked list)
    n1->next = n2;

    n2->prev = n1;
    n2->next = n3;

    n3->prev = n2;
    n3->next = n4;

    n4->prev = n3;

    Node* head = n1;
    Node* tail = n4;

    cout << "Bit meaning: bit0=Visible, bit1=Active, bit2=Locked\n\n";

    cout << "Before Toggling Bit 1 (Active):\n";
    cout << "Forward: ";
    printForward(head);

    cout << "Backward: ";
    printBackwardFromTail(tail);

    cout << "\nAfter Toggling Bit 1 (Active):\n";
   toggleActive(head, tail);

    cout << "Forward: ";
    printForward(head);

    cout << "Backward: ";
    printBackwardFromTail(tail);

    return 0;
}
