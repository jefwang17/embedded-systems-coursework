#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Linear search for unsorted list (cart)
bool linearSearch(const vector<int>& arr, int target) {
    for (int value : arr) {
        if (value == target)
            return true;
    }
    return false;
}

// Binary search for sorted list (catalog)
bool binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == target)
            return true;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}

int main() {
    ifstream cartFile("cart.txt");
    ifstream catalogFile("catalog.txt");

    if (!cartFile || !catalogFile) {
        cout << "Error: Could not open one or both files." << endl;
        return 1;
    }

    vector<int> cart, catalog;
    int id;

    // Read unsorted cart IDs
    while (cartFile >> id)
        cart.push_back(id);
    cartFile.close();

    // Read sorted catalog IDs
    while (catalogFile >> id)
        catalog.push_back(id);
    catalogFile.close();

    // Ask user for product ID to search
    int target;
    cout << "Enter a product ID to search: ";
    cin >> target;

    // Search in both lists
    bool inCart = linearSearch(cart, target);
    bool inCatalog = binarySearch(catalog, target);

    cout << endl;
    cout << "Search Results:" << endl;
    cout << "---------------------------------" << endl;

    if (inCart)
        cout << "Product " << target << " is already in your cart." << endl;
    else
        cout << "Product " << target << " is NOT in your cart." << endl;

    if (inCatalog)
        cout << "Product " << target << " exists in the catalog." << endl;
    else
        cout << "Product " << target << " does NOT exist in the catalog." << endl;

    return 0;
}
