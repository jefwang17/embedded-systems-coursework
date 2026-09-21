#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <iomanip>
#include <numeric>
using namespace std;

// === Lab 5 Sorting Algorithm: Selection Sort ===
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

// === Generate sizes.txt with random integers ===
void generateSizesFile(const char* filename = "sizes.txt",
                       int minCount = 10, int maxCount = 50,
                       int minKB = 100, int maxKB = 5000) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> cnt(minCount, maxCount);
    uniform_int_distribution<int> val(minKB, maxKB);

    int n = cnt(gen);
    ofstream out(filename);
    if (!out) {
        cerr << "Error: cannot write " << filename << "\n";
        return;
    }
    for (int i = 0; i < n; ++i)
        out << val(gen) << '\n';
    out.close();

    cout << "Generated " << n << " random sizes in " << filename << ".\n";
}

// === Read sizes.txt into vector ===
bool readSizes(const char* filename, vector<int>& v) {
    ifstream in(filename);
    if (!in) return false;
    v.clear();
    int x;
    while (in >> x)
        v.push_back(x);
    return true;
}

// === Remove duplicates using two-pointer method ===
size_t dedupInPlace(vector<int>& v) {
    if (v.empty()) return 0;
    size_t w = 1;
    for (size_t r = 1; r < v.size(); ++r) {
        if (v[r] != v[w - 1])
            v[w++] = v[r];
    }
    v.resize(w);
    return w;
}

// === Helper functions ===
long long sumOf(const vector<int>& v) {
    return accumulate(v.begin(), v.end(), 0LL);
}

void printList(const vector<int>& v, const string& title, int cols = 10) {
    cout << "\n" << title << " (N=" << v.size() << "):\n";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << setw(6) << v[i];
        if ((i + 1) % cols == 0 || i + 1 == v.size()) cout << '\n';
    }
}

// === Main Program ===
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Exercise 4: Detecting & Removing Duplicate File Sizes (After Sorting)\n";
    cout << "1) Generate sizes.txt\n"
         << "2) Analyze sizes.txt (sort, dedup, report)\n"
         << "3) Generate + Analyze\n"
         << "4) Exit\n"
         << "Enter choice: " << flush;

    int choice;
    if (!(cin >> choice)) return 0;
    if (choice == 4) return 0;

    if (choice == 1 || choice == 3) {
        generateSizesFile();
        if (choice == 1) return 0;
    }

    vector<int> v;
    if (!readSizes("sizes.txt", v)) {
        cout << "sizes.txt not found; generating one now...\n";
        generateSizesFile();
        if (!readSizes("sizes.txt", v)) {
            cerr << "Error: cannot read sizes.txt\n";
            return 1;
        }
    }

    // Step 1: Sort using your Lab 5 Selection Sort
    selectionSort(v);
    vector<int> sortedBefore = v;
    long long sum_before = sumOf(sortedBefore);

    // Step 2: Remove duplicates in-place
    size_t uniqueCount = dedupInPlace(v);
    long long sum_after = sumOf(v);
    long long saved = sum_before - sum_after;
    double percent_saved = (sum_before == 0) ? 0.0 : 100.0 * saved / sum_before;

    // Step 3: Print results
    printList(sortedBefore, "Original list (sorted copy before dedup)");
    printList(v, "Deduplicated list");

    cout << "\nCounts:\n"
         << "  Original N = " << sortedBefore.size() << "\n"
         << "  Unique   U = " << uniqueCount << "\n"
         << "  Removed    = " << (sortedBefore.size() - uniqueCount) << "\n";

    cout << fixed << setprecision(2);
    cout << "\nTotals (KB):\n"
         << "  sum_before   = " << sum_before << "\n"
         << "  sum_after    = " << sum_after << "\n"
         << "  saved        = " << saved << "\n"
         << "  percent_saved= " << percent_saved << "%\n";

    return 0;
}
