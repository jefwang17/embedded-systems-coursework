#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> // for transform
using namespace std;

int main() {
    // Step 1: declare totals
    double foodTotal = 0.0;
    double transportTotal = 0.0;
    double entertainmentTotal = 0.0;

    // Step 2: open input file
    ifstream fin("expense.txt");
    if (!fin) {
        cerr << "Error: could not open expense.txt for reading.\n";
        return 1;
    }

    // Step 3: open output file
    ofstream fout("expense_report.txt");
    if (!fout) {
        cerr << "Error: could not open expense_report.txt for writing.\n";
        return 1;
    }

    // Skip the first line (record count)
    int recordCount;
    fin >> recordCount;

    // Step 4: process each record
    string category;
    double amount;
    while (fin >> category >> amount) {
        // convert category to lowercase for consistency
        transform(category.begin(), category.end(), category.begin(), ::tolower);

        if (category == "food") {
            foodTotal += amount;
        } else if (category == "transport") {
            transportTotal += amount;
        } else if (category == "entertainment") {
            entertainmentTotal += amount;
        }
        // ignore other categories
    }

    // Step 5: write results
    fout << "food: " << foodTotal << endl;
    fout << "transportation: " << transportTotal << endl;
    fout << "entertainment: " << entertainmentTotal << endl;

    // Step 6: close files
    fin.close();
    fout.close();

    cout << "Report written to expense_report.txt\n";
    return 0;
}
