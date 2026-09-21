#include "Car.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Default constructor
Car::Car() 
    : make(""), registrationNumber(""), startMiles(0.0), endMiles(0.0), costPerMile(0.0), renter("") {}

// Parameterized constructor
Car::Car(const string& mk, const string& regNo, double start, double end, double cost, const string& r)
    : make(mk), registrationNumber(regNo), startMiles(start), endMiles(end), costPerMile(cost), renter(r) {}

// Getters
string Car::getMake() const { return make; }
string Car::getRegistrationNumber() const { return registrationNumber; }
double Car::getStartMiles() const { return startMiles; }
double Car::getEndMiles() const { return endMiles; }
double Car::getCostPerMile() const { return costPerMile; }
string Car::getRenter() const { return renter; }

// Setters
void Car::setStartMiles(double start) { startMiles = start; }
void Car::setEndMiles(double end) { endMiles = end; }
void Car::setCostPerMile(double cost) { costPerMile = cost; }
void Car::setRenter(const string& renterName) { renter = renterName; }

//Computation
double Car::milesDriven() const {
    return (endMiles > startMiles) ? (endMiles - startMiles) : 0.0;

    
    if (endMiles > startMiles){
        return endMiles - startMiles;
    
    }
    else
        return 0.0;
}

double Car::tripCost() const 
{
    return milesDriven() * costPerMile;
}
// Display
void Car::printSummary() const 
{
    cout << fixed << setprecision(2);
    cout << "Car: " << make << " (" << registrationNumber << ")\n";
    cout << "Renter: " <<renter << "\n";
    cout << "Miles Driven: " << milesDriven() << '\n';
    cout << "Trip cost S" << tripCost() << "\n";
    cout << "----------------------------------------------------\n";
}