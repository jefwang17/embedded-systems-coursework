#include "Cafe.h"
#include <cstdlib>   // rand, srand
#include <iostream>  // cout
using namespace std;

string APP_VERSION = "1.0"; // define here for simplicity (extern in header)

// ---------- RNG ----------
void seedRng(unsigned s) { srand(s); }
int nextInt(int minIncl, int maxIncl) {
    if (maxIncl < minIncl) return minIncl;
    return (rand() % (maxIncl - minIncl + 1)) + minIncl;
}

// ---------- File helpers ----------
bool openMenu(ifstream& fin, const string& path) {
    fin.close();
    fin.clear();
    fin.open(path.c_str());
    return static_cast<bool>(fin);
}

// Parse one line: ITEM,weight   (no arrays; simple comma split)
bool readMenuLine(istream& in, string& item, int& weight) {
    string line;
    if (!std::getline(in, line)) return false;

    // Trim leading/trailing spaces (simple)
    while (!line.empty() && (line[0]==' '||line[0]=='\t')) line.erase(0,1);
    while (!line.empty() && (line.back()==' '||line.back()=='\t'||line.back()=='\r')) line.pop_back();
    if (line.empty() || line[0]=='#') return false;

    size_t comma = line.find(',');
    if (comma == string::npos) return false;

    item = line.substr(0, comma);
    string wstr = line.substr(comma + 1);

    // Trim again
    while (!item.empty() && (item[0]==' '||item[0]=='\t')) item.erase(0,1);
    while (!item.empty() && (item.back()==' '||item.back()=='\t')) item.pop_back();
    while (!wstr.empty() && (wstr[0]==' '||wstr[0]=='\t')) wstr.erase(0,1);
    while (!wstr.empty() && (wstr.back()==' '||wstr.back()=='\t')) wstr.pop_back();

    weight = atoi(wstr.c_str());
    if (item.empty() || weight <= 0) return false;
    return true;
}

// Weighted choice with static local spot-check (least-popular every 7 misses)
string chooseItemWeighted(ifstream& fin) {
    // Pass 1: compute total weight and track least-popular item
    fin.clear();
    fin.seekg(0, ios::beg);

    int total = 0;
    string leastItem = "";
    int leastWeight = 0;

    {
        string it; int wt;
        bool firstValid = true;
        while (true) {
            streampos pos = fin.tellg();
            if (!fin.good()) break;
            if (!readMenuLine(fin, it, wt)) continue;
            if (firstValid) { leastItem = it; leastWeight = wt; firstValid = false; }
            if (wt < leastWeight) { leastItem = it; leastWeight = wt; }
            total += wt;
        }
    }

    if (total <= 0) return "Coffee"; // safe default

    // Static local counter as required by lab (spot-check every 7 non-picks)
    static int spotCheckCounter = 0;

    // If counter reached 7, force least-popular and reset
    if (spotCheckCounter >= 7 && !leastItem.empty()) {
        spotCheckCounter = 0;
        cout << "[Spot-Check Triggered] Forcing: " << leastItem << "\n";
        return leastItem;
    }

    // Pass 2: pick by weight
    fin.clear();
    fin.seekg(0, ios::beg);
    int r = nextInt(1, total);

    string chosen = leastItem; // fallback
    string it; int wt;
    int running = 0;

    while (true) {
        if (!readMenuLine(fin, it, wt)) {
            if (fin.eof()) break;
            else continue;
        }
        running += wt;
        if (r <= running) {
            chosen = it;
            break;
        }
    }

    // Update spot-check counter
    if (chosen == leastItem) spotCheckCounter = 0;
    else spotCheckCounter++;

    return chosen;
}

// ---------- Simulation ----------
void processOrder(Barista& worker, const string& menuPath) {
    ifstream fin;
    if (!openMenu(fin, menuPath)) {
        cout << "Could not open menu file: " << menuPath << "\n";
        return;
    }
    string item = chooseItemWeighted(fin);
    worker.serveOne(item);
    cout << worker.getName() << " served: " << item << "\n";
}

void summarizeShift(const Barista& worker) {
    cout << "\n=== Shift Summary ===\n";
    cout << "Barista: " << worker.getName() << "\n";
    cout << "Orders:  " << worker.getOrdersServed() << "\n";
    cout << "Minutes: " << worker.getWorkMinutes()  << "\n";
}
