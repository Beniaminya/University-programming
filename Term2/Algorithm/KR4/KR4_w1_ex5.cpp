#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

int countNodes(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    return 1 + countNodes(root->left) + countNodes(root->right);
}

bool isComplete(Node* root, int index, int count) {
    if (root == nullptr) {
        return true;
    }

    if (index >= count) {
        return false;
    }

    bool left = isComplete(root->left, 2 * index + 1, count);
    bool right = isComplete(root->right, 2 * index + 2, count);

    return left && right;
}

bool isMaxHeap(Node* root) {
    if (root == nullptr) {
        return true;
    }

    if (root->left != nullptr && root->left->value > root->value) {
        return false;
    }

    if (root->right != nullptr && root->right->value > root->value) {
        return false;
    }

    return isMaxHeap(root->left) && isMaxHeap(root->right);
}

bool isMinHeap(Node* root) {
    if (root == nullptr) {
        return true;
    }

    if (root->left != nullptr && root->left->value < root->value) {
        return false;
    }

    if (root->right != nullptr && root->right->value < root->value) {
        return false;
    }

    return isMinHeap(root->left) && isMinHeap(root->right);
}

bool isBinaryHeap(Node* root) {
    int count = countNodes(root);

    if (!isComplete(root, 0, count)) {
        return false;
    }

    if (isMaxHeap(root) || isMinHeap(root)) {
        return true;
    }

    return false;
}

int main() {
    Node* root = new Node(10);
    root->left = new Node(8);
    root->right = new Node(6);
    root->left->left = new Node(4);
    root->left->right = new Node(2);

    if (isBinaryHeap(root)) {
        cout << "Дерево является двоичной кучей" << endl;
    } else {
        cout << "Дерево не является двоичной кучей" << endl;
    }

    return 0;
}