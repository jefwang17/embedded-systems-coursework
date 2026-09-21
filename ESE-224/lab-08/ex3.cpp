#include <iostream>
#include <string>
#include <limits>   
using namespace std;

struct Tab {
    int id;
    string title;
    Tab* next;
    Tab(int i = -1, const string& t = "")
        : id(i), title(t), next(nullptr) {}
};

/* 1. createTab: returns a Tab by value (data only) */
Tab createTab(int id, std::string title) {
    Tab t(id, title);
    return t;
}

/* 2. openTab: push new tab onto stack */
void openTab(Tab*& top, const Tab& newTab) {
    Tab* node = new Tab(newTab.id, newTab.title);
    node->next = top;
    top = node;
}

/* 3. closeTab: pop top tab, write data into `closed`, return false if empty */
bool closeTab(Tab*& top, Tab& closed) {
    if (top == nullptr) {
        return false;
    }
    closed.id = top->id;
    closed.title = top->title;

    Tab* temp = top;
    top = top->next;
    delete temp;
    return true;
}

/* 4. peekTop: return copy of current top (or sentinel if empty) */
Tab peekTop(const Tab* top) {
    if (top == nullptr) {
        return Tab(-1, "");
    }
    return *top;   // copy
}

/* 5. printTabs: print all tabs from top -> bottom */
void printTabs(const Tab* top) {
    if (top == nullptr) {
        cout << "[EMPTY]\n";
        return;
    }
    const Tab* cur = top;
    while (cur) {
        cout << "#" << cur->id << ": " << cur->title << "\n";
        cur = cur->next;
    }
}

/* 6. clearTabs: delete all nodes and set top = nullptr */
void clearTabs(Tab*& top) {
    while (top) {
        Tab* temp = top;
        top = top->next;
        delete temp;
    }
    top = nullptr;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cout << "Enter number of operations: ";
    if (!(cin >> Q)) return 0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n--- Executing Commands ---\n\n";

    Tab* top = nullptr;
    int nextId = 1;

    for (int i = 0; i < Q; ++i) {
        string line;
        if (!std::getline(cin, line)) break;
        if (line.empty()) { --i; continue; }

        cout << line << "\n";   // echo command like sample

        // Parse command word
        string cmd;
        size_t pos = line.find(' ');
        if (pos == string::npos) {
            cmd = line;
        } else {
            cmd = line.substr(0, pos);
        }

        if (cmd == "OPEN") {
            // Title may contain spaces
            string title = (pos == string::npos) ? "" : line.substr(pos + 1);
            Tab t = createTab(nextId++, title);
            openTab(top, t);
            cout << "[OPEN] Added tab #" << t.id << ": " << t.title << "\n";
        }
        else if (cmd == "CLOSE") {
            Tab closed;
            if (closeTab(top, closed)) {
                cout << "[CLOSE] Closed tab #" << closed.id
                     << ": " << closed.title << "\n";
            } else {
                cout << "[CLOSE] No tabs to close\n";
            }
        }
        else if (cmd == "PEEK") {
            Tab t = peekTop(top);
            if (t.id == -1) {
                cout << "[PEEK] No tabs open\n";
            } else {
                cout << "[PEEK] Top tab -> #" << t.id
                     << ": " << t.title << "\n";
            }
        }
        else if (cmd == "SHOW") {
            cout << "Tabs (Top->Bottom):\n";
            printTabs(top);
        }
        else if (cmd == "CLEAR") {
            clearTabs(top);
            cout << "[CLEAR] All tabs closed\n";
        }
        else if (cmd == "EXIT") {
            break;  // optional early stop
        }
    }

    cout << "\n--- Session End ---\n\n";
    cout << "Remaining Tabs (Top->Bottom):\n";
    printTabs(top);

    clearTabs(top);  // final cleanup
    return 0;
}
