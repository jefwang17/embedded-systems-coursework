#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Product.h"
//g++ main.cpp Product.cpp -o products

int main() {
    // 1) Fixed exchange rate (e.g., 0.93)
    const double USD_TO_EUR_RATE = 0.93;

    // 2) User input variables
    std::string name;
    double price_usd = 0.0;

    // 3) Open output file before the loop
    std::ofstream fout("products.dat");
    if (!fout) {
        std::cerr << "Error: could not open products.dat for writing.\n";
        return 1;
    }

    // Optional: formatting for money-like output
    fout << std::fixed << std::setprecision(2);
    std::cout << std::fixed << std::setprecision(2);

    // 5) Sentinel-controlled loop: product name "exit" ends input
    while (true) {
        std::cout << "Enter product name (or 'exit' to finish): ";
        if (!std::getline(std::cin, name)) break;   // input stream ended
        if (name == "exit") break;                  // sentinel

        std::cout << "Enter USD price for \"" << name << "\": ";
        if (!(std::cin >> price_usd)) {
            std::cerr << "Invalid number. Try again.\n";
            // clear error & discard the rest of the line
            std::cin.clear();
            std::string dummy;
            std::getline(std::cin, dummy);
            continue;
        }
        // consume trailing newline before next getline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // 9) Create Product & 10) write immediately to file
        Product p(name, price_usd);
        fout << p.getName() << ", "
             << p.getPriceUSD() << " USD, "
             << p.getPriceEUR(USD_TO_EUR_RATE) << " EUR\n";

        std::cout << "Saved: " << p.getName() << "\n";
    }

    // 11) Close the file
    fout.close();
    std::cout << "All done. Results written to products.dat\n";
    return 0;
}
