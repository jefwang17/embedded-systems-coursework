#include <iostream>
using namespace std;

struct Node {
    int id;
    Node* prev;
    Node* next;
    Node(int v) : id(v), prev(nullptr), next(nullptr) {}
};

class OrderQueue {
private:
    Node* head;   // front of queue
    Node* tail;   // back of queue

public:
    OrderQueue() : head(nullptr), tail(nullptr) {}

    ~OrderQueue() {
        clear();
    }

    // ENQUEUE <order_id>
    void enqueue(int orderId) {
        Node* node = new Node(orderId);
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        cout << "OK ENQUEUE " << orderId << "\n";
    }

    // DEQUEUE
    void dequeue() {
        if (!head) {
            // spec doesn't say what to do on empty, keep it simple:
            cout << "Queue is empty\n";
            return;
        }
        int val = head->id;
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;   // queue became empty
        delete temp;
        cout << "DEQUEUE " << val << "\n";
    }

    // SHOW
    void show() const {
        cout << "Queue: ";
        if (!head) {
            cout << "[EMPTY]\n";
            return;
        }
        Node* cur = head;
        bool first = true;
        while (cur) {
            if (!first) cout << " -> ";
            first = false;
            cout << "[" << cur->id << "]";
            cur = cur->next;
        }
        cout << "\n";
    }

    // REVERSE – in place
    void reverse() {
        if (!head || !head->next) {
            cout << "OK REVERSE\n";
            return; // 0 or 1 element, nothing changes
        }

        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;

        tail = head; // old head will become new tail

        while (curr) {
            next = curr->next;
            curr->next = prev;
            curr->prev = next;   // because links flip
            prev = curr;
            curr = next;
        }

        head = prev; // prev is new head
        cout << "OK REVERSE\n";
    }

    // DELETE <index>  (0-based index)
    void deleteAt(int idx) {
        if (idx < 0 || !head) {
            cout << "OK DELETE idx=" << idx << "\n";
            return;
        }

        Node* cur = head;
        int i = 0;
        while (cur && i < idx) {
            cur = cur->next;
            ++i;
        }

        if (!cur) {
            // index out of range; still acknowledge
            cout << "OK DELETE idx=" << idx << "\n";
            return;
        }

        if (cur->prev) cur->prev->next = cur->next;
        else head = cur->next; // deleting head

        if (cur->next) cur->next->prev = cur->prev;
        else tail = cur->prev; // deleting tail

        delete cur;
        cout << "OK DELETE idx=" << idx << "\n";
    }

    // CLEAR
    void clear() {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
        // Only print when called by command, not destructor
    }

    void clearCommand() {
        clear();
        cout << "OK CLEAR\n";
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    if (!(cin >> Q)) return 0;

    OrderQueue q;
    string cmd;

    for (int i = 0; i < Q; ++i) {
        cin >> cmd;

        if (cmd == "ENQUEUE") {
            int id;
            cin >> id;
            q.enqueue(id);
        } else if (cmd == "DEQUEUE") {
            q.dequeue();
        } else if (cmd == "SHOW") {
            q.show();
        } else if (cmd == "REVERSE") {
            q.reverse();
        } else if (cmd == "DELETE") {
            int idx;
            cin >> idx;
            q.deleteAt(idx);
        } else if (cmd == "CLEAR") {
            q.clearCommand();
        }
    }

    return 0;
}
