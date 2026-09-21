#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <limits>


struct Node {
    std::string title;
    int priority{};
    Node* next{nullptr};
    Node(const std::string& t, int p) : title(t), priority(p), next(nullptr) {}
};

class TaskList {
public:
    TaskList() = default;
    ~TaskList() { clear(); }

    void addTail(const std::string& title, int priority) {
        Node* n = new Node(title, priority);
        if (!head) {
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
        std::cout << "[ADD] Added task: " << title << " (priority=" << priority << ")\n";
    }

    void show() const {
        std::cout << "[SHOW] Current Task List:\n  ";
        Node* cur = head;
        if (!cur) { std::cout << "NULL\n"; return; }
        while (cur) {
            std::cout << cur->title << "(" << cur->priority << ")  ->  ";
            cur = cur->next;
        }
        std::cout << "NULL\n";
    }

    void clear() {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
        std::cout << "[CLEAR] List cleared.\n";
    }

    // In-place insertion sort on the linked list by ascending priority.
    // Stable: inserts AFTER existing nodes of equal priority.
    void organize(bool trace=false) {
        Node dummySortedHead{"", 0};   // dummy head for sorted sublist
        Node* sortedTail = nullptr;     // optional, not strictly needed

        Node* cur = head;
        while (cur) {
            Node* extracted = cur;          // remove from input portion
            cur = cur->next;                // advance input pointer
            extracted->next = nullptr;

            // Find insertion point in the sorted sublist.
            Node* prev = &dummySortedHead;
            Node* scan = dummySortedHead.next;

            // Place AFTER existing equals to keep stability: use < (not <=)
            while (scan && scan->priority <= extracted->priority) {
                // For strict stability: move past equals
                if (scan->priority < extracted->priority) {
                    prev = scan;
                    scan = scan->next;
                } else {
                    // equal: keep moving to insert AFTER the last equal
                    prev = scan;
                    scan = scan->next;
                    while (scan && scan->priority == extracted->priority) {
                        prev = scan;
                        scan = scan->next;
                    }
                    break;
                }
            }

            // Link extracted between prev and scan
            extracted->next = prev->next;
            prev->next = extracted;

            if (trace) {
                std::cout << "[TRACE] Inserted \"" << extracted->title
                          << "\" (p=" << extracted->priority << ") -> ";
                printFrom(dummySortedHead.next);
            }
        }

        // Rebuild head/tail from sorted list
        head = dummySortedHead.next;
        tail = head;
        while (tail && tail->next) tail = tail->next;

        std::cout << "[ORGANIZE] Tasks sorted by ascending priority.\n";
    }

private:
    Node* head{nullptr};
    Node* tail{nullptr};

    static void printFrom(Node* n) {
        if (!n) { std::cout << "NULL\n"; return; }
        while (n) {
            std::cout << n->title << "(" << n->priority << ") -> ";
            n = n->next;
        }
        std::cout << "NULL\n";
    }
};

// --- Helpers ---------------------------------------------------------------

static inline std::string trim(const std::string& s) {
    size_t a = 0, b = s.size();
    while (a < b && std::isspace(static_cast<unsigned char>(s[a]))) ++a;
    while (b > a && std::isspace(static_cast<unsigned char>(s[b-1]))) --b;
    return s.substr(a, b - a);
}

// Parses "ADD <title>|<priority>"
bool parseAdd(const std::string& line, std::string& titleOut, int& prioOut) {
    // Everything after "ADD " is payload
    const std::string prefix = "ADD ";
    if (line.size() < prefix.size()) return false;
    std::string payload = line.substr(prefix.size());
    // Split at last '|' so titles with '|' are still safe if not expected
    size_t bar = payload.rfind('|');
    if (bar == std::string::npos) return false;
    titleOut = trim(payload.substr(0, bar));
    std::string pr = trim(payload.substr(bar + 1));
    try {
        prioOut = std::stoi(pr);
    } catch (...) {
        return false;
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TaskList list;
    bool trace = false;

    int Q = 0;
while (true) {
    std::cout << "Enter number of commands: " << std::flush;
    if (std::cin >> Q && Q > 0) break;
    std::cout << "Please enter a positive integer.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // eat the newline
std::cout << "=== Executing Commands ===\n";


    for (int i = 0; i < Q; ++i) {
        std::string line;
        std::getline(std::cin, line);
        line = trim(line);
        if (line.empty()) { --i; continue; }

        if (line.rfind("ADD ", 0) == 0) {
            std::string title; int p = 0;
            if (parseAdd(line, title, p)) {
                list.addTail(title, p);
            } else {
                std::cout << "[ERROR] Bad ADD format. Use: ADD <title>|<priority>\n";
            }
        } else if (line == "SHOW") {
            list.show();
        } else if (line == "ORGANIZE") {
            list.organize(trace);
        } else if (line == "CLEAR") {
            list.clear();
        } else if (line == "TRACE") {
            trace = true;
            std::cout << "[TRACE] Enabled (will show insert placements during next ORGANIZE).\n";
        } else {
            std::cout << "[WARN] Unknown command: " << line << "\n";
        }
    }

    return 0;
}
