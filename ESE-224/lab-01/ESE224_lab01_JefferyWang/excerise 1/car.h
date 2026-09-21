#ifndef CAR_H
#define CAR_H

#include <string>
using namespace std;

class Car {
private:
    string make;
    string registrationNumber;
    double startMiles;
    double endMiles;
    double costPerMile;
    string renter;

public:
    // Constructors
    Car();
    Car(const string& make, const string& regNo, double start, double end, double cost, const string& renter);

    // Getters
    string getMake() const;
    string getRegistrationNumber() const;
    double getStartMiles() const;
    double getEndMiles() const;
    double getCostPerMile() const;
    string getRenter() const;

    // Setters
    void setStartMiles(double start);
    void setEndMiles(double end);
    void setCostPerMile(double cost);
    void setRenter(const string& renterName);

    // Computations
    double milesDriven() const;
    double tripCost() const;

    // Display
    void printSummary() const;
};

#endif
