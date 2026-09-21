#include "Book.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Constructors
Book::Book() 
    : title(""), author(""), isbn(""), price(0.0) {}

Book::Book(const string& t, const string& a, const string& i, double p)
    : title(t), author(a), isbn(i), price(p < 0.0 ? 0.0 : p) {}

// Accessors
string Book::getTitle()  const { return title;  }
string Book::getAuthor() const { return author; }
string Book::getISBN()   const { return isbn;   }
double Book::getPrice()  const { return price;  }

// Mutators
void Book::setTitle(const string& t)  { title = t;   }
void Book::setAuthor(const string& a) { author = a;  }
void Book::setISBN(const string& i)   { isbn = i;    }
void Book::setPrice(double p)         { price = (p < 0.0 ? 0.0 : p); }

// Behaviors
void Book::displayInfo() const {
    cout << fixed << setprecision(2);
    cout << "Title:  " << title  << "\n"
         << "Author: " << author << "\n"
         << "ISBN:   " << isbn   << "\n"
         << "Price:  $" << price << " (" << priceCategory() << ")\n"
         << "----------------------------------------\n";
}

string Book::priceCategory() const {
    return (price >= 20.0) ? "Premium" : "Standard";
}

void Book::applyDiscount(double percentOff) {
    // Valid range: 0–100; invalid => no change
    if (percentOff < 0.0 || percentOff > 100.0) return;
    price *= (1.0 - percentOff / 100.0);
}
