#ifndef LOOT_H
#define LOOT_H

#include <string>
#include <fstream>
using namespace std;

class LootBox {
private:
    // weights
    int wCommon, wRare, wEpic, wLegendary;
    // pity threshold
    int pityThreshold;
    // counters
    int cCommon, cRare, cEpic, cLegendary;
    // log path
    string logPath;

public:
    LootBox();

    // config & getters
    bool loadConfig(const string& path);
    const string& getLogPath() const;

    // one roll; writes a line into log (already opened by caller)
    void rollOnce(ofstream& out);

    // summary
    void printSummary(ofstream& out) const;
    void printSummaryToConsole() const;
};

#endif
