#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book{
    private:
        string title;
        string author;
        string isbn;
        double price;

    public:
    // Constructors
    Book();
    Book(const string& title, const string& author, const string& isbn, double price);

    // Accessors (const)
    string getTitle()  const;
    string getAuthor() const;
    string getISBN()   const;
    double getPrice()  const;
    // Mutators
    void setTitle(const string& title);
    void setAuthor(const string& author);
    void setISBN(const string& isbn);
    void setPrice(double price);
    // Behaviors
    void   displayInfo() const;      // formatted output with <iomanip>
    string priceCategory() const;    // "Premium" if price >= 20.0 else "Standard"
    void   applyDiscount(double percentOff); // 0–100; invalid => no change
};

#endif
