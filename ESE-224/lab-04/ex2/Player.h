#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
private:
    string name;
    int wins;

public:
    Player(const string& n);
    string makeChoice();     // "Left", "Center", or "Right"
    void incrementWins();    // +1 win
    int getWins() const;     // return wins
    string getName() const;  // return name
};

#endif
