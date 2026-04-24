#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    int height;
    Node* left;
    Node* right;
    Node(int value): data(value), height(1), right(nullptr), left(nullptr) {}
};

int height(Node* node){
    return node ? node->height: 0;
}

int balance_factor(Node* node){
    return (height(node->left) - height(node->right));
}

void updateHeight(Node* node){
    node->height = 1 + max(height(node->left), height(node->right));
}

Node* insert(Node* node, int value){
    if (!node) return new Node(value);
    if (value > node->data){
        node->right = insert(node->right, value);
    }
    else if (value < node->data){
        node->left = insert(node->left, value);
    }
    else return node;//повторяющееся значение идёт мимо
    updateHeight(node);
    return node;
}

Node* searchNode(Node* root, int value){
    if (!root) return nullptr;
    if (root->data == value) return root;
    if (root->data > value) return searchNode(root->right, value);
    if (root->data < value) return searchNode(root->left, value);
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " " << balance_factor(root) << endl;
    preorder(root->left);
    preorder(root->right);
}

int main(){
    Node* tree = new Node(30);
    tree = insert(tree, 26);
    tree = insert(tree, 37);
    tree = insert(tree, 69);
    tree = insert(tree, 15);
    tree = insert(tree, 100);
    tree = insert(tree, 7);
    tree = insert(tree, 59);
    preorder(tree);
}