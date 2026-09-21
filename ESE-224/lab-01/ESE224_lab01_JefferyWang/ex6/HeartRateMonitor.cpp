#include "HeartRateMonitor.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Constructor: sentinel values
HeartRateMonitor::HeartRateMonitor()
    : current(-1.0), average(-1.0), highest(-1.0), lowest(-1.0),
      sum(0.0), count(0) {}

// Getters
double HeartRateMonitor::getCurrent() const { return current; }
double HeartRateMonitor::getAverage() const { return average; }
double HeartRateMonitor::getHighest() const { return highest; }
double HeartRateMonitor::getLowest()  const { return lowest; }
int    HeartRateMonitor::getCount()   const { return count; }

// Add a new reading
void HeartRateMonitor::addReading(double bpm) {
    if (bpm <= 0) return;  // ignore invalid

    if (count == 0) {
        // First valid reading initializes everything
        current = average = highest = lowest = bpm;
        sum = bpm;
        count = 1;
    } else {
        current = bpm;
        sum += bpm;
        count++;
        average = sum / count;
        if (bpm > highest) highest = bpm;
        if (bpm < lowest)  lowest = bpm;
    }
}

// Reset monitor
void HeartRateMonitor::reset() {
    current = average = highest = lowest = -1.0;
    sum = 0.0;
    count = 0;
}

// Display stats
void HeartRateMonitor::printStats() const {
    cout << fixed << setprecision(1);
    cout << "Current: " << current
         << " | Avg: " << average
         << " | High: " << highest
         << " | Low: " << lowest
         << " | Count: " << count
         << "\n";
}
