#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int d) : data(d), left(nullptr), right(nullptr) {}
};

// Insert into BST
Node* insertNode(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }
    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else {
        root->right = insertNode(root->right, value);
    }
    return root;
}

// Find minimum (leftmost)
int findMin(Node* root) {
    if (!root) {
        cout << "Tree is empty.\n";
        return -1;
    }
    while (root->left != nullptr) {
        root = root->left;
    }
    return root->data;
}

// Find maximum (rightmost)
int findMax(Node* root) {
    if (!root) {
        cout << "Tree is empty.\n";
        return -1;
    }
    while (root->right != nullptr) {
        root = root->right;
    }
    return root->data;
}

int main() {
    Node* root = nullptr;
    int n;

    cout << "Enter number of elements to insert into the BST: ";
    cin >> n;

    cout << "Enter " << n << " integer values:\n";

    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        root = insertNode(root, val);
    }

    int minimum = findMin(root);
    int maximum = findMax(root);

    cout << "\nMinimum value in BST: " << minimum << endl;
    cout << "Maximum value in BST: " << maximum << endl;

    return 0;
}
