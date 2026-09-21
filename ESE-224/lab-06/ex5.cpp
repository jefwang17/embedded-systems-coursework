#include <iostream>
#include <string>
using namespace std;

// Prints a message but takes it BY VALUE to demonstrate that edits do NOT persist
void displayMessage(string msg) {
    cout << "Displaying (by value): " << msg << "\n";
    msg = "[Modified inside displayMessage]";
    cout << "Inside function, changed text to: " << msg << "\n";
}

// Permanently updates a message (call-by-reference)
void editMessage(string& msg, const string& newText) {
    msg = newText;
}

// Prints all messages in order by following the provided pointers
void showChain(string* first, string* next1, string* next2) {
    cout << "\nMessage Chain:\n";
    if (first)  cout << *first  << "\n";
    if (next1)  cout << *next1  << "\n";
    if (next2)  cout << *next2  << "\n";
}

int main() {
    // --- Create three messages ---
    string msg1 = "Hi, this is message 1!";
    string msg2 = "Hope you are doing well!";
    string msg3 = "Goodbye!";

    // --- Create pointers that connect the messages in order ---
    string* p1 = &msg1;      // first
    string* next1 = &msg2;   // points to second
    string* next2 = &msg3;   // points to third

    cout << "Initial Messages:\n";
    cout << msg1 << "\n" << msg2 << "\n" << msg3 << "\n";

    // Show initial chain
    showChain(p1, next1, next2);

    // Edit the SECOND message (persist via reference)
    cout << "\nEditing message 2 ...\n";
    editMessage(msg2, "Message 2: Updated successfully.");

    // Show chain again to confirm persistence
    showChain(p1, next1, next2);

    // Demonstrate call-by-value using message 1 (does NOT persist)
    cout << "\nTrying to change message 1 ...\n";
    displayMessage(msg1);
    cout << "Back in main(): " << msg1 << " (unchanged)\n";

    // Edit message 3 using POINTER dereferencing (persists)
    cout << "\nEditing message 3 using pointer dereferencing...\n";
    *next2 = "Message 3: Edited using a pointer!";

    // Final chain
    showChain(p1, next1, next2);
    cout << "\nFinal Message Chain Complete.\n";

    return 0;
}
