#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int d) : data(d), left(nullptr), right(nullptr) {}
};

// Recursively traverse and return sum of all nodes
int traverseAndSum(Node* root, const string& role = "Root") {
    if (root == nullptr) {
        return 0; // Base case
    }

    bool isLeaf = (root->left == nullptr && root->right == nullptr);

    // Print role + value, and mark leaf nodes
    cout << role << ": " << root->data;
    if (isLeaf) {
        cout << " (Leaf)";
    }
    cout << endl;

    // Recursive case: visit left and right
    int leftSum  = traverseAndSum(root->left,  "Left Child");
    int rightSum = traverseAndSum(root->right, "Right Child");

    return root->data + leftSum + rightSum;
}

int main() {

    Node* root = new Node(10);
    root->left = new Node(6);
    root->right = new Node(15);

    root->left->left = new Node(3);
    root->left->right = new Node(8);

    root->right->left = new Node(12);
    root->right->right = new Node(18);

    cout << "Recursive Tree Traversal:" << endl;

    int total = traverseAndSum(root);

    cout << "\nTotal Sum of All Nodes: " << total << endl;

    return 0;
}
