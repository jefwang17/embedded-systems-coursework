#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ifstream infile("manuscript.txt");
    if (!infile) {
        cout << "Error: could not open manuscript.txt" << endl;
        return 1;
    }

    vector<string> words;
    string word;
    while (infile >> word) {
        // make lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        words.push_back(word);
    }
    infile.close();

    int totalDuplicates = 0;
    for (int i = 0; i < words.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (words[i] == words[j]) {
                cout << "Duplicate found: \"" << words[i]
                     << "\" (first seen at index " << j << ")" << endl;
                totalDuplicates++;
                break; // only count once per repeated word
            }
        }
    }

    cout << "Total duplicates: " << totalDuplicates << endl;
    return 0;
}
