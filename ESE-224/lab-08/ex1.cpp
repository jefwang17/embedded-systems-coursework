#include <iostream>
#include <string>

using namespace std;

struct Node {
    string url;
    Node* prev;
    Node* next;
    Node(const string& u) : url(u), prev(nullptr), next(nullptr) {}
};

class BrowserHistory {
private:
    Node* head;    // oldest page
    Node* current; // current page

public:
    // Constructor: initialize with homepage
    BrowserHistory(const string& homepage) {
        head = new Node(homepage);
        current = head;
    }

    // Destructor: free entire list
    ~BrowserHistory() {
        // move to head first
        while (current && current->prev) current = current->prev;
        // delete from head forward
        Node* temp = current;
        while (temp) {
            Node* nxt = temp->next;
            delete temp;
            temp = nxt;
        }
        head = current = nullptr;
    }

    // Visit a new URL, clear forward history
    void visit(const string& url) {
        // first free all nodes after current
        Node* temp = current->next;
        while (temp) {
            Node* nxt = temp->next;
            delete temp;
            temp = nxt;
        }
        current->next = nullptr;

        // create new node and link it
        Node* newNode = new Node(url);
        newNode->prev = current;
        current->next = newNode;
        current = newNode;
    }

    // Move back up to steps pages, return current URL
    string back(int steps) {
        while (steps > 0 && current->prev != nullptr) {
            current = current->prev;
            --steps;
        }
        return current->url;
    }

    // Move forward up to steps pages, return current URL
    string forward(int steps) {
        while (steps > 0 && current->next != nullptr) {
            current = current->next;
            --steps;
        }
        return current->url;
    }

    // Show full history from oldest to newest
    void show() {
        cout << "Browser History:\n";
        // go to head
        Node* temp = current;
        while (temp->prev) temp = temp->prev;
        Node* start = temp;

        bool first = true;
        while (temp) {
            if (!first) cout << " -> ";
            first = false;

            if (temp == current)
                cout << "*[" << temp->url << "]";
            else
                cout << "[" << temp->url << "]";

            temp = temp->next;
        }
        cout << '\n';
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    BrowserHistory* bh = nullptr;

    string cmd;
    for (int i = 0; i < n; ++i) {
        cin >> cmd;

        if (cmd == "INIT") {
            string homepage;
            cin >> homepage;

            // delete previous session if any
            if (bh) {
                delete bh;
                bh = nullptr;
            }
            bh = new BrowserHistory(homepage);
            cout << "Initialized with homepage: " << homepage << "\n";
        }
        else if (cmd == "VISIT") {
            string url;
            cin >> url;
            if (bh) {
                bh->visit(url);
                cout << "Visited: " << url << "\n";
            }
        }
        else if (cmd == "BACK") {
            int steps;
            cin >> steps;
            if (bh) {
                string cur = bh->back(steps);
                cout << cur << "\n";
            }
        }
        else if (cmd == "FORWARD") {
            int steps;
            cin >> steps;
            if (bh) {
                string cur = bh->forward(steps);
                cout << cur << "\n";
            }
        }
        else if (cmd == "SHOW") {
            if (bh) {
                bh->show();
            }
        }
        else if (cmd == "EXIT") {
            break;
        }
    }

    delete bh; // clean up if not null
    return 0;
}
