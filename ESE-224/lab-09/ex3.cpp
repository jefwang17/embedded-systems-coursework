#include <iostream>
using namespace std;
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};
struct ListNode {
    int data;
    ListNode* next;

    ListNode(int d) : data(d), next(nullptr) {}
};

void appendNode(ListNode*& head, ListNode*& tail, int value) {
    ListNode* newNode = new ListNode(value);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void preorderToList(TreeNode* root, ListNode*& head, ListNode*& tail) {
    if (!root) return;

    // Visit root
    appendNode(head, tail, root->data);
    // Traverse left
    preorderToList(root->left, head, tail);
    // Traverse right
    preorderToList(root->right, head, tail);
}

// Print linked list
void printList(ListNode* head) {
    ListNode* curr = head;
    while (curr) {
        cout << curr->data << " -> ";
        curr = curr->next;
    }
    cout << "NULL" << endl;
}

// Bubble sort on singly linked list (ascending)
void bubbleSortList(ListNode* head) {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        ListNode* curr = head;
        while (curr->next) {
            if (curr->data > curr->next->data) {
                // swap data
                int temp = curr->data;
                curr->data = curr->next->data;
                curr->next->data = temp;
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
}

int main() {
   

    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(6);
    root->right = new TreeNode(15);

    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(8);

    root->right->left = new TreeNode(12);
    root->right->right = new TreeNode(18);

    // Convert BST to linked list using preorder traversal
    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    preorderToList(root, head, tail);

    cout << "Linked List BEFORE sorting (Preorder Traversal Order):" << endl;
    printList(head);

    // Sort the linked list in ascending order
    bubbleSortList(head);

    cout << "\nLinked List AFTER sorting (Ascending Order):" << endl;
    printList(head);

    return 0;
}
