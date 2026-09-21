#include "Barista.h"

Barista::Barista(const string& n)
    : name(n), ordersServed(0), workMinutes(0) {}

void Barista::serveOne(const string& item) {
    ordersServed++;

    // Simple workload rules (example from lab): Burrito +3, Smoothie +2, Coffee/Tea/Bagel +1
    if (item == "Breakfast_Burrito") workMinutes += 3;
    else if (item == "Smoothie")     workMinutes += 2;
    else if (item == "Coffee" || item == "Tea" || item == "Bagel") workMinutes += 1;
    else workMinutes += 1; // default +1 min
}

int Barista::getOrdersServed() const { return ordersServed; }
int Barista::getWorkMinutes()  const { return workMinutes; }
string Barista::getName()      const { return name; }
