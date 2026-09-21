#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Character {
    int id;
    string name;
    Character* next;
    Character(int i, const string& n) : id(i), name(n), next(nullptr) {}
};

// 1) createCharacter
Character* createCharacter(int id, const std::string& name) {
    return new Character(id, name);
}

// 2) joinCharacter
void joinCharacter(Character*& head, Character*& tail, const std::string& name, int& count) {
    Character* node = createCharacter(++count, name);
    if (!head) head = tail = node;
    else { tail->next = node; tail = node; }
    cout << "[JOIN] Added: " << name << " (#" << node->id << ")\n";
}

// 3) showRoster
void showRoster(const Character* head) {
    cout << "[SHOW] Current Roster:\n   ";
    const Character* p = head;
    if (!p) { cout << "NULL\n"; return; }
    while (p) {
        cout << "(" << p->id << ") " << p->name << "  ->  ";
        p = p->next;
    }
    cout << "NULL\n";
}

// 4) reorderRoster (in place, stable within odd/even groups)
void reorderRoster(Character*& head) {
    if (!head || !head->next) { cout << "[REORDER] No change.\n"; return; }

    Character *oddHead = nullptr, *oddTail = nullptr;
    Character *evenHead = nullptr, *evenTail = nullptr;

    Character* cur = head;
    bool isOdd = true;  // 1-based positions as we walk
    while (cur) {
        Character* nxt = cur->next;
        cur->next = nullptr;
        if (isOdd) {
            if (!oddHead) oddHead = oddTail = cur;
            else { oddTail->next = cur; oddTail = cur; }
        } else {
            if (!evenHead) evenHead = evenTail = cur;
            else { evenTail->next = cur; evenTail = cur; }
        }
        isOdd = !isOdd;
        cur = nxt;
    }

    // stitch: odds first, then evens
    if (oddTail) oddTail->next = evenHead;
    head = (oddHead ? oddHead : evenHead);
    cout << "[REORDER] Roster reordered: odd positions first.\n";
}

// 5) clearRoster
void clearRoster(Character*& head) {
    Character* p = head;
    while (p) { Character* nxt = p->next; delete p; p = nxt; }
    head = nullptr;
    cout << "[CLEAR] Roster cleared.\n";
}

int main() {
    ios::sync_with_stdio(false);

    Character* head = nullptr;
    Character* tail = nullptr;
    int count = 0; // auto-incrementing IDs

    int Q;
    if (!(cin >> Q)) return 0;
    string dummy; getline(cin, dummy); // consume endline

    for (int i = 0; i < Q; ++i) {
        string line;
        if (!getline(cin, line)) break;
        if (line.empty()) { --i; continue; }

        if (line.rfind("JOIN ", 0) == 0) {
            string name = line.substr(5);
            // trim leading/trailing spaces
            size_t a = name.find_first_not_of(" \t\r\n");
            size_t b = name.find_last_not_of(" \t\r\n");
            name = (a == string::npos ? "" : name.substr(a, b - a + 1));
            joinCharacter(head, tail, name, count);
        }
        else if (line == "SHOW") {
            showRoster(head);
        }
        else if (line == "REORDER") {
            reorderRoster(head);
        }
        else if (line == "CLEAR") {
            clearRoster(head);
            tail = nullptr; count = 0;
        }
        // unknown commands are ignored
    }
    // cleanup (in case CLEAR wasn't called)
    if (head) clearRoster(head);
    return 0;
}
