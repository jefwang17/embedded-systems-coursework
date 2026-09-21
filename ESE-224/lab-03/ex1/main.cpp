#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Step 1: Counters
    int homepageCount = 0;
    int aboutCount = 0;

    // Step 2: Open input file
    ifstream fin("website_log.txt");
    if (!fin) {
        cerr << "Error: Could not open website_log.txt" << endl;
        return 1;
    }

    // Step 3: Open output file
    ofstream fout("visitor_report.txt");
    if (!fout) {
        cerr << "Error: Could not open visitor_report.txt" << endl;
        return 1;
    }

    // Step 4: Read file line by line (EOF-controlled loop)
    string line;
    while (getline(fin, line)) {
        // Step 5: Categorize
        if (line == "homepage") {
            homepageCount++;
        } else if (line == "about_page") {
            aboutCount++;
        }
        // Other pages ignored
    }

    // Step 6: Write results to output
    fout << "Homepage visits: " << homepageCount << endl;
    fout << "About page visits: " << aboutCount << endl;

    // Step 7: Close files
    fin.close();
    fout.close();

    cout << "Visitor report generated in visitor_report.txt" << endl;
    return 0;
}
