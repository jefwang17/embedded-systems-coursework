#include <iostream>
#include <vector>
#include <string>
using namespace std;

class FileEntry {
protected:
    int priority;
public:
    FileEntry(int p) : priority(p) {}
    virtual ~FileEntry() {}
    int getPriority() const { return priority; }
    virtual void printInfo() const = 0;
};

class TextFile : public FileEntry {
    string contents;
public:
    TextFile(int p, const string& c) : FileEntry(p), contents(c) {}
    void printInfo() const override {
        cout << "TextFile (priority = " << priority << "): " << contents << '\n';
    }
};

class BinaryFile : public FileEntry {
    vector<unsigned char> data;
public:
    BinaryFile(int p, const vector<unsigned char>& d) : FileEntry(p), data(d) {}
    void printInfo() const override {
        cout << "BinaryFile (priority = " << priority << "): " 
             << data.size() << " bytes\n";
    }
};

struct Node {
    FileEntry* entry;
    Node* left;
    Node* right;
    Node(FileEntry* e) : entry(e), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, FileEntry* e) {
    if (!root) return new Node(e);
    if (e->getPriority() < root->entry->getPriority())
        root->left = insert(root->left, e);
    else
        root->right = insert(root->right, e);
    return root;
}

void inorder(Node* root, vector<FileEntry*>& out) {
    if (!root) return;
    inorder(root->left, out);
    out.push_back(root->entry);
    inorder(root->right, out);
}

void heapify(vector<FileEntry*>& heap, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left]->getPriority() < heap[smallest]->getPriority())
        smallest = left;
    if (right < n && heap[right]->getPriority() < heap[smallest]->getPriority())
        smallest = right;

    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapify(heap, n, smallest);
    }
}

void buildMinHeap(vector<FileEntry*>& heap) {
    int n = (int)heap.size();
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(heap, n, i);
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Node* root = nullptr;

    root = insert(root, new TextFile(10, "notes"));
    root = insert(root, new BinaryFile(3, vector<unsigned char>{0x20, 0x11, 0xFF}));
    root = insert(root, new TextFile(7, "todo list"));
    root = insert(root, new BinaryFile(5, vector<unsigned char>{0x01, 0x02}));
    root = insert(root, new TextFile(1, "very urgent message"));

    vector<FileEntry*> heapData;
    inorder(root, heapData);

    buildMinHeap(heapData);

    cout << "Processing files in order of priority:\n";

    int heapSize = (int)heapData.size();
    while (heapSize > 0) {
        heapData[0]->printInfo();
        swap(heapData[0], heapData[heapSize - 1]);
        --heapSize;
        if (heapSize > 0)
            heapify(heapData, heapSize, 0);
    }

    for (FileEntry* f : heapData)
        delete f;

    deleteTree(root);

    return 0;
}
