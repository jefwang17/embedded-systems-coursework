#include "Loot.h"
#include "Rand.h"
#include <iostream>   // cout
#include <ctime>      // time, localtime
#include <iomanip>    // put_time (if not available, we’ll print plain numbers)

LootBox::LootBox()
: wCommon(75), wRare(20), wEpic(4), wLegendary(1),   // reasonable defaults
  pityThreshold(10),
  cCommon(0), cRare(0), cEpic(0), cLegendary(0),
  logPath("loot_log.txt")
{}

// Parse simple key=value lines; ignore unknown keys.
// No arrays/vectors — process one line at a time.
bool LootBox::loadConfig(const string& path) {
    ifstream fin(path.c_str());
    if (!fin) return false;

    string line;
    while (std::getline(fin, line)) {
        // trim leading/trailing spaces (simple, no <regex>)
        while (!line.empty() && (line[0]==' ' || line[0]=='\t' || line[0]=='#')) {
            if (line[0]=='#') { line.clear(); break; }
            line.erase(0,1);
        }
        if (line.empty()) continue;

        size_t eq = line.find('=');
        if (eq == string::npos) continue;

        string key = line.substr(0, eq);
        string val = line.substr(eq + 1);

        // trim simple spaces on both ends of val
        while (!key.empty() && (key[0]==' '||key[0]=='\t')) key.erase(0,1);
        while (!val.empty() && (val[0]==' '||val[0]=='\t')) val.erase(0,1);
        while (!key.empty() && (key.back()==' '||key.back()=='\t')) key.pop_back();
        while (!val.empty() && (val.back()==' '||val.back()=='\t')) val.pop_back();

        if (key == "common")        wCommon     = std::atoi(val.c_str());
        else if (key == "rare")     wRare       = std::atoi(val.c_str());
        else if (key == "epic")     wEpic       = std::atoi(val.c_str());
        else if (key == "legendary")wLegendary  = std::atoi(val.c_str());
        else if (key == "pity")     pityThreshold= std::atoi(val.c_str());
        else if (key == "log_file") logPath     = val;
        // ignore others (e.g., theme, bonus)
    }
    return true;
}

const string& LootBox::getLogPath() const { return logPath; }

// Weighted selection + static pity (stateful local)
void LootBox::rollOnce(ofstream& out) {
    // Local static keeps state across calls (per spec)
    static int pityCount = 0;   // persists across all LootBox::rollOnce calls

    bool pityTriggered = false;

    // If pity reached threshold BEFORE selection → force Legendary
    if (pityCount >= pityThreshold && pityThreshold > 0) {
        pityTriggered = true;
        pityCount = 0;
        cLegendary++;
        out << "Legendary [PITY TRIGGERED]\n";
        return;
    }

    // Weighted pick
    const int W = wCommon + wRare + wEpic + wLegendary;
    int r = Rand::nextInt(1, (W > 0 ? W : 1));

    string result;
    if (r <= wCommon) {
        cCommon++; result = "Common";
    } else if (r <= wCommon + wRare) {
        cRare++; result = "Rare";
    } else if (r <= wCommon + wRare + wEpic) {
        cEpic++; result = "Epic";
    } else {
        cLegendary++; result = "Legendary";
    }

    if (result == "Legendary") {
        pityCount = 0; // reset after Legendary
    } else {
        pityCount = pityCount + 1;
    }

    out << result << (pityTriggered ? " [PITY TRIGGERED]" : "") << "\n";
}

void LootBox::printSummary(ofstream& out) const {
    int total = cCommon + cRare + cEpic + cLegendary;
    out << "\n--- Session Summary ---\n";
    out << "Total: "      << total      << "\n";
    out << "Common: "     << cCommon    << "\n";
    out << "Rare: "       << cRare      << "\n";
    out << "Epic: "       << cEpic      << "\n";
    out << "Legendary: "  << cLegendary << "\n";
}

void LootBox::printSummaryToConsole() const {
    int total = cCommon + cRare + cEpic + cLegendary;
    cout << "\n--- Session Summary ---\n";
    cout << "Total: "      << total      << "\n";
    cout << "Common: "     << cCommon    << "\n";
    cout << "Rare: "       << cRare      << "\n";
    cout << "Epic: "       << cEpic      << "\n";
    cout << "Legendary: "  << cLegendary << "\n";
}
