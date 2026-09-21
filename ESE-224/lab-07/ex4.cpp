#include <iostream>
#include <string>
#include <iomanip>

using std::cin;
using std::cout;
using std::string;

/* ------------------ Function Templates ------------------ */
template <typename T>
void swapVals(T* a, T* b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

template <typename T, typename Comparator>
void bubbleSort(T* begin, T* end, Comparator comp) {
    // classic bubble sort using pointer traversal; early-exit if no swaps
    if (end - begin <= 1) return;

    for (T* i = begin; i < end - 1; ++i) {
        bool swapped = false;
        for (T* j = begin; j < (end - 1) - (i - begin); ++j) {
            // If next element should come before *j by the comparator, swap
            if (comp(*(j + 1), *j)) {
                swapVals(j, j + 1);
                swapped = true;
            }
        }
        if (!swapped) break;  // already sorted
    }
}

/* ------------------ Helper to run a case ------------------ */
template <typename T>
void runCase() {
    int N;
    cin >> N;

    T* arr = new T[N];

    // read N values (space-separated)
    for (int i = 0; i < N; ++i) cin >> arr[i];

    string order;
    cin >> order;  // "ASC" or "DESC"

    // comparators: return true if lhs should come BEFORE rhs
    if (order == "ASC") {
        bubbleSort(arr, arr + N, [](const T& a, const T& b) { return a < b; });
    } else { // DESC
        bubbleSort(arr, arr + N, [](const T& a, const T& b) { return a > b; });
    }

    // print on one line, space-separated
    for (int i = 0; i < N; ++i) {
        if (i) cout << ' ';
        cout << arr[i];
    }
    cout << '\n';

    delete[] arr;
}

/* ----------------------------- main ----------------------------- */
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string type;
    if (!(cin >> type)) return 0;

    if (type == "INT") {
        runCase<int>();
    } else if (type == "DOUBLE") {
        // (No special precision required by the prompt; printing default format)
        runCase<double>();
    } else if (type == "STRING") {
        runCase<string>();
    }
    return 0;
}
