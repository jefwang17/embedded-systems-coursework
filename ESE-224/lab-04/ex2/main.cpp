#include <iostream>
#include <ctime>      // time()
#include <cstdlib>    // srand(), rand()
#include "Player.h"
using namespace std;


// g++ main.cpp Player.cpp -o main
// Function prototype
void playRound(Player& shooter, Player& keeper);

int main() {
    srand(time(0));   // seed RNG once

    Player shooter("Shooter");
    Player keeper("Goalkeeper");

    for (int round = 1; round <= 5; ++round) {
        cout << "\nRound " << round << ":\n";
        playRound(shooter, keeper);
    }

    cout << "\nFinal Results:\n";
    cout << shooter.getName() << " Wins = " << shooter.getWins() << endl;
    cout << keeper.getName() << " Wins = " << keeper.getWins() << endl;

    if (shooter.getWins() > keeper.getWins())
        cout << shooter.getName() << " wins the game!\n";
    else if (keeper.getWins() > shooter.getWins())
        cout << keeper.getName() << " wins the game!\n";
    else
        cout << "It's a draw!\n";

    return 0;
}

// Function definition
void playRound(Player& shooter, Player& keeper) {
    string s = shooter.makeChoice();
    string g = keeper.makeChoice();

    cout << shooter.getName() << " chooses " << s << endl;
    cout << keeper.getName() << " dives " << g << endl;

    if (s == g) {
        cout << "SAVE! " << keeper.getName() << " wins this round.\n";
        keeper.incrementWins();
    } else {
        cout << "GOAL! " << shooter.getName() << " wins this round.\n";
        shooter.incrementWins();
    }
}
