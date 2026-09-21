#include <iostream>
#include <string>
#include <ctime> // time
#include "Barista.h"
#include "Cafe.h"

using namespace std;

static void clearLine() { cin.clear(); cin.ignore(10000, '\n'); }
// g++ main.cpp Cafe.cpp Barista.cpp -o main
int readPositiveInt(const string& prompt) {
    int n;
    while (true) {
        cout << prompt;
        if (cin >> n && n > 0) return n;
        cout << "Invalid. Try again.\n";
        clearLine();
    }
}

int main() {
    cout << "Campus Cafe Simulator v" << APP_VERSION << "\n"; 

    seedRng((unsigned)time(0)); // per lab style

    Barista worker("Jeffery");
    const string MENU = "menu.txt";

    char again;
    do {
        int customers = readPositiveInt("Customers this rush: ");

        for (int i = 0; i < customers; ++i) {
            processOrder(worker, MENU);
        }

        summarizeShift(worker);

        cout << "\nRun another rush? (Y/N): ";
        cin >> again;
        clearLine();
    } while (again == 'Y' || again == 'y');

    cout << "Goodbye!\n";
    return 0;
}
