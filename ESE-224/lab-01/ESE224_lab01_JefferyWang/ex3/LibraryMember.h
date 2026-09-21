#ifndef LIBRARY_MEMBER_H
#define LIBRARY_MEMBER_H

#include <string>
using std::string;

class LibraryMember {
private:
    string memberID;     // Unique identifier
    string name;         // Member's name
    int    borrowedBooks;
    int    maxBooks;     // default: 5

public:
    // Constructors
    LibraryMember();  // memberID="", name="", borrowedBooks=0, maxBooks=5
    LibraryMember(const string& id, const string& nm, int maxAllowed);

    // Getters (optional but handy)
    string getMemberID()   const;
    string getName()       const;
    int    getBorrowed()   const;
    int    getMaxBooks()   const;

    // Actions
    bool borrowBook(int count);  // validate count and capacity; print error & return false if invalid
    bool returnBook(int count);  // validate count and holdings; print error & return false if invalid

    // Display
    void displayInfo() const;
};

#endif
