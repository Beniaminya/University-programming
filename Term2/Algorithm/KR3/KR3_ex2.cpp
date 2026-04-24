#include <iostream>
using namespace std;

struct Node {
    int data;
    int height;
    Node* left;
    Node* right;
    Node(int value) : data(value), height(1), left(nullptr), right(nullptr) {}
};

int height(Node* node) {
    return node ? node->height : 0;
}

int balance_factor(Node* node) {
    return height(node->left) - height(node->right);
}

void updateHeight(Node* node) {
    if (node)
        node->height = 1 + max(height(node->left), height(node->right));
}

// Forward declaration
Node* balance(Node* node);

Node* turnRight(Node* A) {
    Node* B      = A->left;
    Node* BRight = B->right;  
    B->right = A;
    A->left  = BRight;
    updateHeight(A);
    updateHeight(B);
    return B;
}

Node* turnLeft(Node* A) {
    Node* B     = A->right;
    Node* BLeft = B->left;
    B->left  = A;
    A->right = BLeft;
    updateHeight(A);
    updateHeight(B);
    return B;
}

Node* balance(Node* node) {
    updateHeight(node);
    int bf = balance_factor(node);

    // LL
    if (bf > 1 && balance_factor(node->left) >= 0)
        return turnRight(node);

    // LR
    if (bf > 1 && balance_factor(node->left) < 0) {
        node->left = turnLeft(node->left);
        return turnRight(node);
    }

    // RR:
    if (bf < -1 && balance_factor(node->right) <= 0)
        return turnLeft(node);

    // RL
    if (bf < -1 && balance_factor(node->right) > 0) {
        node->right = turnRight(node->right);
        return turnLeft(node);
    }

    return node;
}

Node* insert(Node* node, int value) {
    if (!node) return new Node(value);

    if (value > node->data)
        node->right = insert(node->right, value);
    else if (value < node->data)
        node->left = insert(node->left, value);
    else
        return node; // повторяющееся значение игнорируем

    return balance(node);
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

int main() {
    Node* root = nullptr;

    for (int val : {30, 20, 10, 25, 35, 5, 15})
        root = insert(root, val);

    cout << "Preorder: ";
    preorder(root);
    return 0;
}