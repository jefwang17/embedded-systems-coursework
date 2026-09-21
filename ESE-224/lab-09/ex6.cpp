#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int d) : data(d), left(nullptr), right(nullptr) {}
};

// Inorder traversal -> sorted list
void inorder(Node* root, vector<int>& vals) {
    if (!root) return;
    inorder(root->left, vals);
    vals.push_back(root->data);
    inorder(root->right, vals);
}

// Check if any two numbers sum to k
bool findTwoSum(Node* root, int k) {
    vector<int> vals;
    inorder(root, vals);

    int left = 0;
    int right = vals.size() - 1;

    while (left < right) {
        int sum = vals[left] + vals[right];
        if (sum == k) return true;
        else if (sum < k) left++;
        else right--;
    }
    return false;
}

int main() {
 
    Node* root = new Node(5);
    root->left = new Node(3);
    root->right = new Node(6);
    root->left->left = new Node(2);
    root->left->right = new Node(4);
    root->right->right = new Node(7);

    cout << "Case 1 (k = 9): ";
    cout << (findTwoSum(root, 9) ? "True" : "False") << endl;

    cout << "Case 2 (k = 28): ";
    cout << (findTwoSum(root, 28) ? "True" : "False") << endl;

    return 0;
}
