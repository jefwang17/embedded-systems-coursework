#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

// Encrypt function
string encrypt(const string& text, int k) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char((c - base + k) % 26 + base);
        } else {
            result += c;
        }
    }
    return result;
}

// Decrypt function
string decrypt(const string& text, int k) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char((c - base - k + 26) % 26 + base);
        } else {
            result += c;
        }
    }
    return result;
}

int main() {
    ifstream infile("messages.txt");
    if (!infile) {
        cout << "Error: could not open messages.txt" << endl;
        return 1;
    }

    string line;
    string allText = "";
    int key = 0;
    bool keyFound = false;   // ✅ added

    // Step 1 & 2: Read file and detect first numeric Caesar shift key
    while (getline(infile, line)) {
        allText += line + "\n";
        if (!keyFound) {
            for (char c : line) {
                if (isdigit(c)) {
                    key = c - '0';
                    keyFound = true;
                    break;   // ✅ stop reading once first digit found
                }
            }
        }
    }
    infile.close();

    cout << "Caesar shift value (k): " << key << endl;
    cout << "=== Encrypted Messages (from file) ===" << endl;
    cout << allText << endl;

    cout << "=== Decrypted Messages ===" << endl;
    stringstream ss(allText);
    string msg;
    string decryptedLines[100];
    int count = 0;

    // Step 3: Decrypt each line
    while (getline(ss, msg)) {
        string dec = decrypt(msg, key);
        decryptedLines[count++] = dec;
        cout << dec << endl;
    }

    // Step 4: Keyword search
    cout << endl;
    string keyword;
    cout << "Enter keyword to search: ";
    cin >> keyword;

    for (int i = 0; i < count; i++) {
        if (decryptedLines[i].find(keyword) != string::npos) {
            cout << "Keyword \"" << keyword << "\" found in: " << decryptedLines[i] << endl;
        }
    }

    return 0;
}
