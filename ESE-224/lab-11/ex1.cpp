#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    string make;
    string model;
    int year;

public:
    Vehicle(string mk, string md, int yr) : make(mk), model(md), year(yr) {}
    virtual void displayInfo() const {
        cout << "Vehicle Info:\n";
        cout << "Make: " << make << ", Model: " << model << ", Year: " << year << endl;
    }
    virtual ~Vehicle() {}
};

class Car : public Vehicle {
private:
    int numberOfDoors;

public:
    Car(string mk, string md, int yr, int d) : Vehicle(mk, md, yr), numberOfDoors(d) {}
    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << "Number of Doors: " << numberOfDoors << endl;
    }
};

class Truck : public Vehicle {
private:
    float payloadCapacity;

public:
    Truck(string mk, string md, int yr, float p) : Vehicle(mk, md, yr), payloadCapacity(p) {}
    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << "Payload Capacity: " << payloadCapacity << " tons" << endl;
    }
};

class Bike : public Vehicle {
private:
    bool hasGear;

public:
    Bike(string mk, string md, int yr, bool g) : Vehicle(mk, md, yr), hasGear(g) {}
    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << "Has Gear: " << (hasGear ? "Yes" : "No") << endl;
    }
};

int main() {
    Vehicle* v[3];

    v[0] = new Car("Toyota", "Corolla", 2020, 4);
    v[1] = new Truck("Ford", "F-150", 2018, 1.5f);
    v[2] = new Bike("Yamaha", "MT-15", 2021, true);

    for (int i = 0; i < 3; i++) {
        v[i]->displayInfo();
        cout << endl;
    }

    for (int i = 0; i < 3; i++) {
        delete v[i];
    }

    return 0;
}
