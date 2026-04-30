#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Node(int val) : data(val), left(nullptr), right(nullptr), parent(nullptr) {}
};

void rotateRight(Node*& root, Node* x) {
    Node* y = x->left;
    if (!y) return;

    x->left = y->right;
    if (y->right) y->right->parent = x;

    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->right = x;
    x->parent = y;
}

void rotateLeft(Node*& root, Node* x) {
    Node* y = x->right;
    if (!y) return;

    x->right = y->left;
    if (y->left) y->left->parent = x;

    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void splay(Node*& root, Node* x) {
    if (!x) return;

    while (x->parent) {
        Node* par = x->parent;
        Node* gp = par->parent;

        if (!gp) {
            // Zig: один поворот
            if (x == par->left) rotateRight(root, par);
            else rotateLeft(root, par);
        } else if (x == par->left && par == gp->left) {
            // Zig-Zig (LL)
            rotateRight(root, gp);
            rotateRight(root, par);
        } else if (x == par->right && par == gp->right) {
            // Zig-Zig (RR)
            rotateLeft(root, gp);
            rotateLeft(root, par);
        } else if (x == par->right && par == gp->left) {
            // Zig-Zag (LR)
            rotateLeft(root, par);
            rotateRight(root, gp);
        } else {
            // Zig-Zag (RL)
            rotateRight(root, par);
            rotateLeft(root, gp);
        }
    }
    root = x;
}

Node* find(Node*& root, int data) {
    Node* cur = root;
    Node* last = nullptr;
    while (cur) {
        last = cur;
        if (data < cur->data) cur = cur->left;
        else if (data > cur->data) cur = cur->right;
        else {
            splay(root, cur);
            return cur;
        }
    }
    if (last) splay(root, last);
    return nullptr;
}

void insert(Node*& root, int data) {
    if (!root) {
        root = new Node(data);
        return;
    }

    Node* cur = root;
    Node* par = nullptr;
    while (cur) {
        par = cur;
        if (data < cur->data) cur = cur->left;
        else if (data > cur->data) cur = cur->right;
        else {
            splay(root, cur);
            return;
        }
    }

    Node* nd = new Node(data);
    nd->parent = par;
    if (data < par->data) par->left = nd;
    else par->right = nd;

    splay(root, nd);
}

Node* findMax(Node*& sub) {
    if (!sub) return nullptr;
    Node* cur = sub;
    while (cur->right) cur = cur->right;
    splay(sub, cur);
    return sub;
}

void erase(Node*& root, int data) {
    if (!find(root, data)) return; // ключ не найден

    // Удаляемый узел — теперь корень
    Node* leftSub = root->left;
    Node* rightSub = root->right;
    delete root;

    if (!leftSub) {
        root = rightSub;
        if (root) root->parent = nullptr;
        return;
    }
    if (!rightSub) {
        root = leftSub;
        if (root) root->parent = nullptr;
        return;
    }

    leftSub->parent = nullptr;
    rightSub->parent = nullptr;

    // Поднимаем максимум левого поддерева в его корень
    root = leftSub;
    findMax(root);

    root->right = rightSub;
    rightSub->parent = root;
}

void inorder(Node* nd) {
    if (!nd) return;
    inorder(nd->left);
    cout << nd->data << " ";
    inorder(nd->right);
}

int main() {
    Node* root = nullptr;

    int arr[] = {7, 3, 18, 10, 22, 8, 11, 26};
    for (int v : arr) insert(root, v);
    cout << "Inorder: "; inorder(root); cout << endl;
    find(root, 10);
    cout << "После поиска 10, корень: " << root->data << endl;

    find(root, 3);
    cout << "После поиска 3, корень: " << root->data << endl;

    erase(root, 26);
    cout << "После удаления 26: "; inorder(root); cout << endl;

    erase(root, 18);
    cout << "После удаления 18: "; inorder(root); cout << endl;

    cout << "Текущий корень: " << root->data << endl;
    erase(root, root->data);
    cout << "После удаления корня: "; inorder(root); cout << endl;

    cout << "Inorder до дубликата: "; inorder(root); cout << endl;
    insert(root, 8);
    cout << "После вставки дубликата 8: "; inorder(root); cout << endl;

    erase(root, 99);
    cout << "После удаления несущ. 99: "; inorder(root); cout << endl;

    return 0;
}