#include "GameInventory.h"
#include <iostream>
#include <iomanip>
#include <type_traits>

template <class T>
GameInventory<T>::GameInventory() : head(nullptr), count(0) {
    static_assert(std::is_arithmetic<T>::value, "T must be numeric");
}

template <class T>
GameInventory<T>::~GameInventory() {
    clear();
}

template <class T>
void GameInventory<T>::addItem(const std::string& name, const T& attribute, double value) {
    Item<T>* n = new Item<T>(name, attribute, value);
    // push-front so "most recent" is head
    n->next = head;
    head = n;
    ++count;
}

template <class T>
bool GameInventory<T>::removeMostRecent(Item<T>& out) {
    if (!head) return false;
    Item<T>* n = head;
    head = head->next;
    out = *n;             // copy fields
    out.next = nullptr;   // do not leak pointer outward
    delete n;
    --count;
    return true;
}

template <class T>
bool GameInventory<T>::retrieveMostRecent(Item<T>& out) const {
    if (!head) return false;
    out = *head;
    out.next = nullptr;
    return true;
}

template <class T>
double GameInventory<T>::totalValue() const {
    double s = 0.0;
    for (Item<T>* p = head; p; p = p->next) s += p->value;
    return s;
}

template <class T>
double GameInventory<T>::averageAttribute() const {
    if (count == 0) return 0.0;
    long double s = 0.0;
    for (Item<T>* p = head; p; p = p->next) s += static_cast<long double>(p->attribute);
    return static_cast<double>(s / static_cast<long double>(count));
}

template <class T>
void GameInventory<T>::displayInventory() const {
    using std::cout;
    using std::fixed;
    using std::setprecision;

    cout << "[SHOW] Inventory (most recent first):\n";
    if (!head) {
        cout << "  (empty)\n";
        return;
    }
    int idx = 0;
    for (Item<T>* p = head; p; p = p->next, ++idx) {
        cout << "  [" << idx << "] " << p->name
             << "  attr=" << p->attribute
             << "  value=" << fixed << setprecision(2) << p->value << "\n";
    }
}

template <class T>
void GameInventory<T>::clear() {
    Item<T>* p = head;
    while (p) {
        Item<T>* nx = p->next;
        delete p;
        p = nx;
    }
    head = nullptr;
    count = 0;
}

template <class T>
std::size_t GameInventory<T>::size() const { return count; }

// ---------- explicit template instantiations so we can keep defs in a .cpp ----------
template class GameInventory<int>;
template class GameInventory<double>;
template struct Item<int>;
template struct Item<double>;
