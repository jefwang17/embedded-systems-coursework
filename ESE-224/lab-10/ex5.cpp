#include <iostream>
using namespace std;

// Return winner (1-based index) of the circular game
int findWinner(int n, int k) {
    int winner = 0;            // 0-based index
    for (int i = 1; i <= n; ++i) {
        winner = (winner + k) % i;
    }
    return winner + 1;         // convert to 1-based friend number
}

int main() {
    int n, k;

    cout << "Enter number of friends (n): ";
    cin >> n;

    cout << "Enter step count (k): ";
    cin >> k;

    int winner = findWinner(n, k);

    cout << "The winner of the game is friend #" << winner << endl;

    return 0;
}
