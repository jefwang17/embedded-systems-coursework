#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int k) {
    if (!root) return new Node(k);
    if (k < root->key)
        root->left = insert(root->left, k);
    else
        root->right = insert(root->right, k);
    return root;
}

void inorder(Node* root, vector<int>& out) {
    if (!root) return;
    inorder(root->left, out);
    out.push_back(root->key);
    inorder(root->right, out);
}

void heapify(vector<int>& heap, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left] < heap[smallest])
        smallest = left;
    if (right < n && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapify(heap, n, smallest);
    }
}

void buildMinHeap(vector<int>& heap) {
    int n = (int)heap.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(heap, n, i);
    }
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Node* root = nullptr;

    int values[] = {50, 20, 70, 10, 30, 60, 90};
    int size = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < size; ++i) {
        root = insert(root, values[i]);
    }

    vector<int> sortedKeys;
    inorder(root, sortedKeys);

    buildMinHeap(sortedKeys);

    cout << "Min-Heap array representation:\n";
    for (int x : sortedKeys) {
        cout << x << " ";
    }
    cout << endl;

    deleteTree(root);
    return 0;
}
