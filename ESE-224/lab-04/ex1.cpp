#include <iostream>   // cout, cin, cerr
#include <cstdlib>    // rand(), srand()
#include <ctime>      // time()
#include <iomanip>    // fixed, setprecision, setw
using namespace std;

// -----------------------------------------------------------
// Step 1: FUNCTION PROTOTYPES
// -----------------------------------------------------------

// Return a random integer in [1..6], simulating a fair die.
int rollDice();

// Simulate 'n' rolls, updating six separate counters by reference.
void simulateRolls(int n,
                   int& c1, int& c2, int& c3,
                   int& c4, int& c5, int& c6);

// Print probabilities and raw counts for each face.
void printProbabilities(int n,
                        int c1, int c2, int c3,
                        int c4, int c5, int c6);

// -----------------------------------------------------------
// MAIN PROGRAM FLOW
// -----------------------------------------------------------
int main() {

    // Step 2: Seed RNG once so results differ on each run.
    srand(time(0)); // RNG seeding

    // Step 3: Ask the user how many experiments to run.
    int experiments = 0;
    cout << "Enter number of experiments: ";
    if (!(cin >> experiments) || experiments <= 0) {
        cerr << "Invalid number of experiments.\n";
        return 1;
    }

    // Step 4–8: Repeat for each experiment
    for (int e = 1; e <= experiments; ++e) {
        int n = 0;
        cout << "\nExperiment " << e << "\nHow many rolls? ";
        if (!(cin >> n) || n <= 0) {
            cerr << "Invalid number of rolls. Skipping this experiment.\n";
            continue;
        }

        // Step 5: Declare/Reset six separate counters (no arrays)
        int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0;

        // Step 6: Simulate rolls; update counters using a switch
        simulateRolls(n, c1, c2, c3, c4, c5, c6);

        // Step 7: Print probabilities for each face
        printProbabilities(n, c1, c2, c3, c4, c5, c6);
    }

    return 0; // normal program end
}

// -----------------------------------------------------------
// FUNCTION DEFINITIONS
// -----------------------------------------------------------

// Step 8: rollDice()
int rollDice() {
    return (rand() % 6) + 1; // rand() % 6 gives 0..5; +1 gives 1..6
}

// Step 8: simulateRolls()
void simulateRolls(int n,
                   int& c1, int& c2, int& c3,
                   int& c4, int& c5, int& c6) {
    for (int i = 0; i < n; ++i) {
        int face = rollDice();
        switch (face) {
            case 1: ++c1; break;
            case 2: ++c2; break;
            case 3: ++c3; break;
            case 4: ++c4; break;
            case 5: ++c5; break;
            case 6: ++c6; break;
        }
    }
}

// Step 8: printProbabilities()
void printProbabilities(int n,
                        int c1, int c2, int c3,
                        int c4, int c5, int c6) {
    cout << "\n--- Dice Roll Probabilities ---\n";
    cout << fixed << setprecision(2);

    auto pct = [n](int count) { return (count * 100.0) / n; };

    cout << "Face 1: " << setw(6) << pct(c1) << "% (" << c1 << "/" << n << ")\n";
    cout << "Face 2: " << setw(6) << pct(c2) << "% (" << c2 << "/" << n << ")\n";
    cout << "Face 3: " << setw(6) << pct(c3) << "% (" << c3 << "/" << n << ")\n";
    cout << "Face 4: " << setw(6) << pct(c4) << "% (" << c4 << "/" << n << ")\n";
    cout << "Face 5: " << setw(6) << pct(c5) << "% (" << c5 << "/" << n << ")\n";
    cout << "Face 6: " << setw(6) << pct(c6) << "% (" << c6 << "/" << n << ")\n";
}
