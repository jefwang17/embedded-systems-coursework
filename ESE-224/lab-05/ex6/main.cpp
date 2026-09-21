#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

class ShoppingList {
public:
    // Ask user for a filename and open it
    bool fileOpen(ifstream &in) {
        string filename;
        cout << "Enter items filename (e.g., items.txt): ";
        getline(cin, filename);
        if (filename.empty()) filename = "items.txt";   // default
        in.open(filename);
        return in.good();
    }

    // Read all items & prices, then print neatly in tabular format
    void printAll() {
        items.clear();
        ifstream in;
        if (!fileOpen(in)) {
            cout << "Error: could not open file.\n";
            return;
        }

        string item;
        double price;
        while (in >> item >> price) {
            items.push_back({item, price});
        }
        in.close();

        cout << "\n=== Shopping List ===\n";
        cout << left << setw(10) << "Item" << right << setw(10) << "Price\n";
        cout << string(20, '-') << endl;
        cout.setf(ios::fixed);
        cout << setprecision(2);

        for (auto &p : items)
            cout << left << setw(10) << p.first
                 << right << setw(10) << p.second << endl;
    }

    // Print the same list but transposed
    void printTranspose() {
        if (items.empty()) {
            cout << "No items loaded.\n";
            return;
        }

        cout << "\n=== Shopping List (Transposed) ===\n";
        const int W = 10;
        cout.setf(ios::fixed);
        cout << setprecision(2);

        // header row
        for (auto &p : items)
            cout << left << setw(W) << p.first;
        cout << endl;

        // price row
        for (auto &p : items)
            cout << left << setw(W) << p.second;
        cout << endl;
    }

private:
    vector<pair<string, double>> items;
};

int main() {
    ShoppingList list;
    list.printAll();
    list.printTranspose();
    return 0;
}
