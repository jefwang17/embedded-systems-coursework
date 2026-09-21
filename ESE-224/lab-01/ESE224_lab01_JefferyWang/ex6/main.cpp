#include "HeartRateMonitor.h"
#include <iostream>
using namespace std;

// g++ main.cpp HeartRateMonitor.cpp -o main
int main() {
    HeartRateMonitor hr;

    cout << "== Initial state ==\n";
    hr.printStats();

    cout << "\n== Adding readings ==\n";
    hr.addReading(72.5);
    hr.addReading(75.0);
    hr.addReading(69.2);
    hr.addReading(80.1);
    hr.printStats();

    cout << "\n== Resetting ==\n";
    hr.reset();
    hr.printStats();

    return 0;
}
