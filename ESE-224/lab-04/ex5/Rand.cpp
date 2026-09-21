#include "Rand.h"
#include <cstdlib> // rand, srand

void Rand::seed(unsigned s) { std::srand(s); }

int Rand::nextInt(int minIncl, int maxIncl) {
    if (maxIncl < minIncl) return minIncl;
    return (std::rand() % (maxIncl - minIncl + 1)) + minIncl;
}

double Rand::next01() {
    return std::rand() / (RAND_MAX + 1.0);
}
