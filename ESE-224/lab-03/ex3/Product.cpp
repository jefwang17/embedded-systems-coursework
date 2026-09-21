#include "Product.h"

static const double USD_TO_EUR_RATE = 0.93;

Product::Product(const std::string& n, double usd)
    : name(n), price_usd(usd) {}

std::string Product::getName() const {
    return name;
}

double Product::getPriceUSD() const {
    return price_usd;
}

double Product::getPriceEUR() const {
    return price_usd * USD_TO_EUR_RATE;
}
