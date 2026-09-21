#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Function to sort a vector in ascending order using Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i; // assume current element is the minimum
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j; // update minimum index
        }
        // swap the found minimum with the current element
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int main() {
    // Step 2: Open the file
    ifstream infile("customers.txt");
    if (!infile) {
        cout << "Error: Could not open file." << endl;
        return 1;
    }

    // Step 3: Read from file into a vector
    vector<int> customers;
    int id;
    while (infile >> id) {
        customers.push_back(id);
    }
    infile.close();

    // Step 4: Sort the vector using custom Selection Sort
    selectionSort(customers);

    // Optional: print sorted IDs
    cout << "Sorted customer IDs: ";
    for (int num : customers) {
        cout << num << " ";
    }
    cout << endl;

    int target;
    cout << "Enter customer ID to search: ";
    cin >> target;

    // Perform binary search
    int left = 0;
    int right = customers.size() - 1;
    bool found = false;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (customers[mid] == target) {
            found = true;
            break;
        } else if (customers[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Step 5: Print result
    if (found) {
        cout << "Customer ID " << target << " found in the database!" << endl;
    } else {
        cout << "Customer ID " << target << " not found." << endl;
    }

    return 0;
}
