#ifndef BARISTA_H
#define BARISTA_H

#include <string>
using namespace std;

class Barista {
private:
    string name;
    int ordersServed;
    int workMinutes;

public:
    Barista(const string& n);

    void serveOne(const string& item); // +orders, +minutes per item
    int  getOrdersServed() const;
    int  getWorkMinutes() const;
    string getName() const;
};

#endif
