#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Base class
class Character {
protected:
    string name;

public:
    // Default constructor
    Character() : name("Unknown") {}

    // Parameterized constructor
    Character(const string& n) : name(n) {}

    // Virtual destructor (good practice for base classes)
    virtual ~Character() = default;

    // Virtual method
    virtual void makeSound() const {
        cout << name << " makes a sound." << endl;
    }
};

// Derived class: Order1
class Order1 : public Character {
public:
    // Constructor passes name to base class
    Order1(const string& n) : Character(n) {}

    // Override makeSound()
    void makeSound() const override {
        cout << name
             << " says: Two number 9s, a number 9 large, a number 6 with extra dip, "
             << "a number 7, two number 45s, one with cheese, and a large soda."
             << endl;
    }
};

// Derived class: Order2
class Order2 : public Character {
public:
    // Constructor passes name to base class
    Order2(const string& n) : Character(n) {}

    // Override makeSound()
    void makeSound() const override {
        cout << name
             << " says: Big Mac's a Big Mac, but they call it Le Big Mac!"
             << endl;
    }
};

int main() {
    // 1. Create objects
    Order1 c1("Big Smoke");
    Order2 c2("Vincent");

    // 2–3. Direct calls
    cout << "Direct calls:" << endl;
    c1.makeSound();
    c2.makeSound();
    cout << endl;

    // 4. Polymorphic calls via base-class pointers
    cout << "Polymorphic calls via base-class pointers:" << endl;
    vector<Character*> chars;
    chars.push_back(&c1);
    chars.push_back(&c2);

    for (Character* ch : chars) {
        ch->makeSound();  // virtual dispatch
    }

    return 0;
}
