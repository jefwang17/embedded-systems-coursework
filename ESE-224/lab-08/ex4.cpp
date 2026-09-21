#include <iostream>
#include <string>

using namespace std;

/********** QUEUE (FIFO) **********/
struct QNode {
    int id;
    QNode* next;
    QNode(int v) : id(v), next(nullptr) {}
};

void enqueue(QNode*& front, QNode*& rear, int id) {
    QNode* node = new QNode(id);
    if (!front) {
        front = rear = node;
    } else {
        rear->next = node;
        rear = node;
    }
    cout << "OK ENQUEUE " << id << "\n";
}

bool dequeue(QNode*& front, QNode*& rear, int& idOut) {
    if (!front) return false;
    QNode* temp = front;
    idOut = temp->id;
    front = front->next;
    if (!front) rear = nullptr;
    delete temp;
    return true;
}

void showQueue(const QNode* front) {
    cout << "Queue: ";
    if (!front) {
        cout << "[EMPTY]\n";
        return;
    }
    const QNode* cur = front;
    bool first = true;
    while (cur) {
        if (!first) cout << " -> ";
        first = false;
        cout << "[" << cur->id << "]";
        cur = cur->next;
    }
    cout << "\n";
}

void clearQueue(QNode*& front, QNode*& rear) {
    while (front) {
        QNode* tmp = front;
        front = front->next;
        delete tmp;
    }
    rear = nullptr;
}

/********** STACK (LIFO) **********/
struct SNode {
    int id;
    SNode* next;
    SNode(int v) : id(v), next(nullptr) {}
};

void pushStack(SNode*& top, int id) {
    SNode* node = new SNode(id);
    node->next = top;
    top = node;
    cout << "OK BURST_PUSH " << id << "\n";
}

bool popStack(SNode*& top, int& idOut) {
    if (!top) return false;
    SNode* temp = top;
    idOut = temp->id;
    top = top->next;
    delete temp;
    return true;
}

void showStack(const SNode* top) {
    cout << "Stack(top->bottom): ";
    if (!top) {
        cout << "[EMPTY]\n";
        return;
    }
    const SNode* cur = top;
    bool first = true;
    while (cur) {
        if (!first) cout << " -> ";
        first = false;
        cout << "[" << cur->id << "]";
        cur = cur->next;
    }
    cout << "\n";
}

void clearStack(SNode*& top) {
    while (top) {
        SNode* tmp = top;
        top = top->next;
        delete tmp;
    }
}

/********** MAIN SIMULATION **********/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    QNode* qFront = nullptr;
    QNode* qRear  = nullptr;
    SNode* sTop   = nullptr;

    string cmd;

    while (cin >> cmd) {
        if (cmd == "EXIT") {
            break;
        }
        if (cmd == "ENQUEUE") {
            int id;
            cin >> id;
            cout << "> ENQUEUE " << id << "\n";
            enqueue(qFront, qRear, id);
        }
        else if (cmd == "DEQUEUE") {
            cout << "> DEQUEUE\n";
            int served;
            if (dequeue(qFront, qRear, served)) {
                cout << "DEQUEUE " << served << "\n";
            } else {
                cout << "DEQUEUE FAILED (queue empty)\n";
            }
        }
        else if (cmd == "BURST_PUSH") {
            int id;
            cin >> id;
            cout << "> BURST_PUSH " << id << "\n";
            pushStack(sTop, id);
        }
        else if (cmd == "BURST_POP") {
            cout << "> BURST_POP\n";
            int served;
            if (popStack(sTop, served)) {
                cout << "BURST_POP " << served << "\n";
            } else {
                cout << "BURST_POP FAILED (stack empty)\n";
            }
        }
        else if (cmd == "TRANSFER") {
            cout << "> TRANSFER\n";
            int moved = 0;
            int id;
            // dequeue from front and push onto stack
            while (dequeue(qFront, qRear, id)) {
                SNode* node = new SNode(id);
                node->next = sTop;
                sTop = node;
                ++moved;
            }
            cout << "OK TRANSFER " << moved << " tickets\n";
        }
        else if (cmd == "SHOW_QUEUE") {
            cout << "> SHOW_QUEUE\n";
            showQueue(qFront);
        }
        else if (cmd == "SHOW_STACK") {
            cout << "> SHOW_STACK\n";
            showStack(sTop);
        }
        else if (cmd == "CLEAR") {
            cout << "> CLEAR\n";
            clearQueue(qFront, qRear);
            clearStack(sTop);
            cout << "OK CLEAR\n";
        }
        else {
            // unknown command, just ignore or report
            // consume rest of line if any
        }
    }

    // final cleanup
    clearQueue(qFront, qRear);
    clearStack(sTop);

    return 0;
}
