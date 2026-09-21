#include "Player.h"
#include <cstdlib>   // rand()

Player::Player(const string& n) : name(n), wins(0) {}

string Player::makeChoice() {
    int x = rand() % 3 + 1;  // 1..3
    if (x == 1) return "Left";
    else if (x == 2) return "Center";
    else return "Right";
}

void Player::incrementWins() { wins = wins + 1; }

int Player::getWins() const { return wins; }

string Player::getName() const { return name; }
