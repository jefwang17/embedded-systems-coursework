#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

struct Song {
    string title, artist;
    int seconds;
    bool liked;
    Song* next;
    Song(const string& t, const string& a, int s)
        : title(t), artist(a), seconds(s), liked(false), next(nullptr) {}
};

struct Playlist {
    Song* head = nullptr;
    Song* tail = nullptr;
    Song* current = nullptr;

    ~Playlist() { clear(); }

    static bool split3(const string& line, string& a, string& b, string& c) {
        size_t p1 = line.find('|');
        if (p1 == string::npos) return false;
        size_t p2 = line.find('|', p1 + 1);
        if (p2 == string::npos) return false;
        a = line.substr(0, p1);
        b = line.substr(p1 + 1, p2 - p1 - 1);
        c = line.substr(p2 + 1);
        return true;
    }

    static void printTime(int s) {
        cout << setw(2) << setfill('0') << s / 60
             << ":" << setw(2) << setfill('0') << s % 60
             << setfill(' ');
    }

    void add(const string& title, const string& artist, int s) {
        Song* n = new Song(title, artist, s);
        if (!head) head = tail = current = n;
        else { tail->next = n; tail = n; }
        cout << "[ADD] Added: " << title << " - " << artist << " (";
        printTime(s);
        cout << ")\n";
    }

    int length() const {
        int n = 0; for (Song* p = head; p; p = p->next) ++n; return n;
    }

    Song* at(int i) const {
        Song* p = head; int idx = 0;
        while (p && idx < i) { p = p->next; ++idx; }
        return (idx == i) ? p : nullptr;
    }

    void like(int i) {
        Song* s = at(i);
        if (!s) { cout << "[LIKE] Invalid index.\n"; return; }
        s->liked = true;
        cout << "[LIKE] Liked: [" << i << "] " << s->title << "\n";
    }

    void skip() {
        if (!head) return;
        if (!current) current = head;
        else current = (current->next ? current->next : head);
        cout << "[SKIP] Now playing: " << current->title << " - "
             << current->artist << " (";
        printTime(current->seconds);
        cout << ")\n";
    }

    void now() const {
        if (!current) { cout << "[NOW] No song.\n"; return; }
        cout << "[NOW] Now playing: " << current->title << " - "
             << current->artist << " (";
        printTime(current->seconds);
        cout << ")\n";
    }

    void show() const {
        cout << "[SHOW] Current Playlist:\n";
        Song* p = head; int i = 0;
        while (p) {
            cout << (p == current ? "-> " : "   ");
            cout << "[" << i << "] " << p->title << " - " << p->artist << " (";
            printTime(p->seconds);
            cout << ")";
            if (p->liked) cout << " [liked]";
            cout << "\n";
            p = p->next; ++i;
        }
        if (!head) cout << "(empty)\n";
    }

    void removeAt(int i) {
        if (!head) return;
        if (i == 0) {
            Song* del = head;
            cout << "[REMOVE] Removed: [0] " << del->title << " - " << del->artist << "\n";
            head = head->next;
            if (current == del) current = head;
            if (tail == del) tail = head;
            delete del; return;
        }
        Song* prev = head;
        for (int j = 0; prev && j < i - 1; ++j) prev = prev->next;
        if (!prev || !prev->next) { cout << "[REMOVE] Invalid index.\n"; return; }
        Song* del = prev->next;
        prev->next = del->next;
        if (tail == del) tail = prev;
        if (current == del) current = (del->next ? del->next : head);
        cout << "[REMOVE] Removed: [" << i << "] " << del->title << " - " << del->artist << "\n";
        delete del;
    }

    void stats() const {
        int c = 0, liked = 0, tot = 0;
        for (Song* p = head; p; p = p->next) {
            ++c; tot += p->seconds; if (p->liked) ++liked;
        }
        cout << "[STATS] Songs: " << c << "  Duration: ";
        printTime(tot);
        cout << "  Liked: " << liked << "\n";
    }

    void clear() {
        Song* p = head;
        while (p) { Song* nxt = p->next; delete p; p = nxt; }
        head = tail = current = nullptr;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(&cout);        // <-- DO NOT set to nullptr (blocks prompt flush)

    int q;
    cout << "Enter number of operations: " << flush;    // force flush
    if (!(cin >> q)) return 0;

    string dummy;
    getline(cin, dummy);   // consume newline

    cout << "\n--- Executing Commands ---\n";

    Playlist pl;

    for (int k = 0; k < q; ++k) {
        string line;
        getline(cin, line);   // waits for your next command

        if (line.empty()) { --k; continue; }

        if (line.rfind("ADD ", 0) == 0) {
            string a,b,c;
            if (!Playlist::split3(line.substr(4), a,b,c)) continue;
            int s = stoi(c);
            pl.add(a,b,s);
        }
        else if (line.rfind("LIKE ", 0) == 0) {
            int idx; istringstream(line.substr(5)) >> idx;
            pl.like(idx);
        }
        else if (line.rfind("REMOVE ", 0) == 0) {
            int idx; istringstream(line.substr(7)) >> idx;
            pl.removeAt(idx);
        }
        else if (line == "SHOW")  pl.show();
        else if (line == "SKIP")  pl.skip();
        else if (line == "NOW")   pl.now();
        else if (line == "STATS") pl.stats();
    }

    cout << "\n--- Session End ---\n";
    pl.stats();
}
