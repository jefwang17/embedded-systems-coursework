#ifndef GAME_INVENTORY_H
#define GAME_INVENTORY_H

#include <string>
#include <type_traits>
#include <cstddef>

template <class T>
struct Item {
    std::string name;
    T attribute;        // numeric only
    double value;
    Item<T>* next;
    Item(const std::string& n, const T& a, double v) : name(n), attribute(a), value(v), next(nullptr) {}
};

template <class T>
class GameInventory {
public:
    GameInventory();
    ~GameInventory();

    // rule of 5 (disable copying to keep ownership simple for course exercise)
    GameInventory(const GameInventory&) = delete;
    GameInventory& operator=(const GameInventory&) = delete;
    GameInventory(GameInventory&&) = delete;
    GameInventory& operator=(GameInventory&&) = delete;

    void addItem(const std::string& name, const T& attribute, double value);  // push-front (most-recent at head)
    bool removeMostRecent(Item<T>& out);                // POP; returns false if empty
    bool retrieveMostRecent(Item<T>& out) const;        // PEEK; returns false if empty
    double totalValue() const;                          // sum of value
    double averageAttribute() const;                    // average of attribute (0.0 if empty)
    void displayInventory() const;                      // print most-recent first
    void clear();                                       // delete all nodes
    std::size_t size() const;

private:
    Item<T>* head;
    std::size_t count;
};

#endif // GAME_INVENTORY_H
