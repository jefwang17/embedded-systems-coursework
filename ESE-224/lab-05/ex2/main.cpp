#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Movie {
    string title;
    int rating;
};

// Function to sort movies by rating in descending order
void Sort(Movie arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].rating > arr[maxIndex].rating)
                maxIndex = j;
        }
        if (maxIndex != i) {
            Movie temp = arr[i];
            arr[i] = arr[maxIndex];
            arr[maxIndex] = temp;
        }
    }
}

int main() {
    ifstream infile("movies.txt");
    if (!infile) {
        cout << "Error: Could not open file." << endl;
        return 1;
    }

    Movie movies[100];
    int count = 0;

    // Read titles and ratings
    while (infile >> movies[count].title >> movies[count].rating) {
        count++;
    }
    infile.close();

    cout << left << setw(20) << "Original List" << endl;
    cout << "------------------------" << endl;
    for (int i = 0; i < count; i++) {
        cout << left << setw(15) << movies[i].title
             << right << setw(5) << movies[i].rating << endl;
    }

    Sort(movies, count);

    cout << endl << left << setw(20) << "Sorted List (Descending)" << endl;
    cout << "------------------------" << endl;
    for (int i = 0; i < count; i++) {
        cout << left << setw(15) << movies[i].title
             << right << setw(5) << movies[i].rating << endl;
    }

    return 0;
}
