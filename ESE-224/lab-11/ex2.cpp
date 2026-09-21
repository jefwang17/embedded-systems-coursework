#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Animal {
protected:
    string species;
    int age;

public:
    Animal(const string& sp, int a) : species(sp), age(a) {}
    virtual double calculateDailyFoodCost() const = 0;
    virtual ~Animal() {}
};

class Lion : public Animal {
private:
    double meatConsumptionKg;

public:
    Lion(const string& sp, int a, double meatKg)
        : Animal(sp, a), meatConsumptionKg(meatKg) {}

    double calculateDailyFoodCost() const override {
        return meatConsumptionKg * 5.50;
    }
};

class Penguin : public Animal {
private:
    int fishCount;

public:
    Penguin(const string& sp, int a, int fish)
        : Animal(sp, a), fishCount(fish) {}

    double calculateDailyFoodCost() const override {
        return fishCount * 0.85;
    }
};

int main() {
    vector<Animal*> zoo;

    zoo.push_back(new Lion("Lion", 5, 8.0));
    zoo.push_back(new Penguin("Penguin", 3, 12));
    zoo.push_back(new Lion("Lion", 10, 12.5));
    zoo.push_back(new Penguin("Penguin", 1, 7));

    cout << "Daily food costs for zoo animals:\n";
    for (size_t i = 0; i < zoo.size(); ++i) {
        cout << "Animal " << i + 1 << ": $"
             << zoo[i]->calculateDailyFoodCost()
             << " per day\n";
    }

    for (Animal* a : zoo) {
        delete a;
    }

    return 0;
}
