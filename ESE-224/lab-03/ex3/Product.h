#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    std::string name;
    double price_usd;

public:
    // Constructor
    Product(const std::string& n, double usd);

    // Getters
    std::string getName() const;
    double getPriceUSD() const;

    // Convert USD -> EUR using fixed rate (0.93)
    double getPriceEUR() const;
};

#endif
