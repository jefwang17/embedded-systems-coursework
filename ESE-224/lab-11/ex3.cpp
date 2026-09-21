#include <iostream>
#include <vector>
using namespace std;

void printArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

void minHeapify(vector<int>& arr, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void buildMinHeap(vector<int>& arr) {
    int n = (int)arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        minHeapify(arr, n, i);
    }
}

void minHeapSort(vector<int>& arr) {
    int n = (int)arr.size();
    vector<int> sorted;
    sorted.reserve(n);

    int heapSize = n;
    while (heapSize > 0) {
        sorted.push_back(arr[0]);
        swap(arr[0], arr[heapSize - 1]);
        --heapSize;
        if (heapSize > 0)
            minHeapify(arr, heapSize, 0);
    }

    arr = sorted;
}

int main() {
    vector<int> arr = {5, 3, 8, 4, 1, 2};

    cout << "Original Array: ";
    printArray(arr);

    buildMinHeap(arr);
    cout << "After Min-Heap construction: ";
    printArray(arr);

    minHeapSort(arr);
    cout << "Sorted Array: ";
    printArray(arr);

    return 0;
}
