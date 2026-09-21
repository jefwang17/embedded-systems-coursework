#include <iostream>
#include <fstream>
#include <string>
#include <ctime>    // time
#include "Rand.h"
#include "Loot.h"
using namespace std;
// g++ main.cpp loot.cpp Rand.cpp -o main
int readPositiveInt(const string& label) {
    int n;
    while (true) {
        cout << label;
        if (cin >> n && n > 0) return n;
        cout << "Invalid. Try again.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

int main() {
    // 1) Seed RNG once (exactly as taught)
    Rand::seed((unsigned)time(0));  // srand(time(0)); inside Rand:contentReference[oaicite:2]{index=2}

    // 2) Construct LootBox and load config file
    LootBox box;
    // Try user file; still OK if missing — defaults apply per spec:contentReference[oaicite:3]{index=3}
    box.loadConfig("loot_config.txt");

    // 3) Ask how many rolls
    int N = readPositiveInt("How many rolls? ");

    // 4) Open log file (append)
    ofstream log(box.getLogPath().c_str(), ios::app);
    if (!log) {
        cout << "Could not open log file. Exiting.\n";
        return 1;
    }

    // Optional: start header
    log << "---- New Session ----\n";

    // 6) Loop N times
    for (int i = 1; i <= N; ++i) {
        box.rollOnce(log);
    }

    // 7) Write summary to log and console
    box.printSummary(log);
    box.printSummaryToConsole();

    log.close();
    return 0;
}
