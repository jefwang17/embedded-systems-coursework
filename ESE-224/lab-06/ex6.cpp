#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <cstdlib>  // rand, srand
#include <ctime>    // time
using namespace std;

const int N = 8;
const int SHIP_COUNT = 5;
const int SIZES[SHIP_COUNT] = {4, 3, 3, 2, 2};
const char EMPTY='.', SHIP='S', HIT='X', MISS='o';

// ---- helpers (as in spec) ----
bool canPlace(char ships[N][N], int r, int c, int len, bool horiz) {
    if (horiz) {
        if (c + len > N) return false;
        for (int k = 0; k < len; ++k)
            if (ships[r][c + k] != EMPTY) return false; // overlaps
    } else {
        if (r + len > N) return false;
        for (int k = 0; k < len; ++k)
            if (ships[r + k][c] != EMPTY) return false; // overlaps
    }
    return true; // safe to place
}

void placeOne(char ships[N][N], int len) {
    while (true) {
        bool horiz = (rand() % 2 == 0); // 50% chance horizontal/vertical
        int r = rand() % N;
        int c = rand() % N;
        if (canPlace(ships, r, c, len, horiz)) {
            if (horiz)
                for (int k = 0; k < len; ++k) ships[r][c + k] = SHIP;
            else
                for (int k = 0; k < len; ++k) ships[r + k][c] = SHIP;
            return; // placed successfully
        }
    }
}

void placeAll(char ships[N][N]) {
    for (int i = 0; i < SHIP_COUNT; ++i)
        placeOne(ships, SIZES[i]);
}

bool parseCoord(const string& s, int& r, int& c) {
    if (s.size() != 2) return false;
    char rowChar = toupper(s[0]);
    char colChar = s[1];
    if (rowChar < 'A' || rowChar >= 'A' + N) return false;
    if (colChar < '1' || colChar >  '8')     return false;
    r = rowChar - 'A';
    c = colChar - '1';
    return true;
}

// ---- pretty board (your preferred format) ----
void printBoard(char view[N][N], int hits, int totalHits, int ammo) {
    cout << "\n    ";
    for (int c = 1; c <= N; ++c) cout << c << (c==N?'\n':' ');
    for (int r = 0; r < N; ++r) {
        cout << char('A'+r) << " | ";
        for (int c = 0; c < N; ++c) {
            cout << view[r][c];
            if (c != N-1) cout << ' ';
        }
        cout << '\n';
    }
    cout << "Hits: " << hits << "/" << totalHits
         << "   Ammo left: " << ammo << "\n";
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    char ships[N][N], view[N][N];
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            ships[i][j] = view[i][j] = EMPTY;

    placeAll(ships);

    const int totalHits = 4 + 3 + 3 + 2 + 2; // 14
    int hits = 0, ammo = 40;

    cout << "Battleship 8x8\nEnter coordinates (e.g. C5). Type Q to quit.\n";

    while (hits < totalHits && ammo > 0) {
        printBoard(view, hits, totalHits, ammo);
        cout << "Enter shot: ";
        string input; cin >> input;
        if (!input.empty() && (input[0]=='Q' || input[0]=='q')) break;

        int r, c;
        if (!parseCoord(input, r, c)) {
            cout << "Invalid coordinate. Use A-H followed by 1-8 (e.g. D4)\n";
            continue;
        }
        if (view[r][c] == HIT || view[r][c] == MISS) {
            cout << "Already fired at " << input << "!\n";
            continue;
        }

        ammo--;
        if (ships[r][c] == SHIP) { cout << "Hit!\n";  view[r][c] = HIT;  ++hits; }
        else                     { cout << "Miss.\n"; view[r][c] = MISS; }
    }

    cout << "\n=== GAME OVER ===\n";
    printBoard(view, hits, totalHits, ammo);

    if (hits == totalHits)      cout << "You sank all ships! Congratulations!\n";
    else if (ammo == 0)         cout << "Out of ammo. Some ships remain unfound.\n";
    else                        cout << "Game exited early.\n";

    // Reveal ships
    cout << "\n--- Ship Locations (for verification) ---\n";
    cout << "    "; for (int c = 1; c <= N; ++c) cout << c << ' '; cout << "\n";
    for (int r = 0; r < N; ++r) {
        cout << char('A'+r) << ' ';
        for (int c = 0; c < N; ++c) cout << ships[r][c] << ' ';
        cout << "\n";
    }

    return 0;
}
