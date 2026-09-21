#ifndef HEART_RATE_MONITOR_H
#define HEART_RATE_MONITOR_H

class HeartRateMonitor {
private:
    double current, average, highest, lowest, sum;
    int count;

public:
    // Constructors
    HeartRateMonitor();  // initialize to sentinel state

    // Getters
    double getCurrent() const;
    double getAverage() const;
    double getHighest() const;
    double getLowest() const;
    int    getCount()   const;

    // Actions
    void addReading(double bpm);  // add new heart rate (ignore <= 0)
    void reset();                 // reset to sentinel state

    // Display
    void printStats() const;      // one-line formatted summary
};

#endif
