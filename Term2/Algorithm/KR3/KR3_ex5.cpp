#include <iostream>
using namespace std;
enum Color { Red, Black };
 
struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Color color;
    Node(int val) : data(val), left(nullptr), right(nullptr), parent(nullptr), color(Red) {}
};
 
bool isRed(Node* nd)   { return nd != nullptr && nd->color == Red; }
bool isBlack(Node* nd) { return nd == nullptr  || nd->color == Black; }
 
Node* grandparent(Node* nd) {
    if (nd && nd->parent)
        return nd->parent->parent;
    return nullptr;
}
 
Node* uncle(Node* nd) {
    Node* gp = grandparent(nd);
    if (!gp) return nullptr;
    return (nd->parent == gp->left) ? gp->right : gp->left;
}
 
void rotateLeft(Node*& root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
 
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
 
    y->left = x;
    x->parent = y;
}
 
void rotateRight(Node*& root, Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
 
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
 
    y->right = x;
    x->parent = y;
}
 
void fixInsert(Node*& root, Node* nd) {
    while (nd != root && isRed(nd->parent)) {
        Node* par = nd->parent;
        Node* gp = grandparent(nd);
        Node* unc = uncle(nd);
 
        if (isRed(unc)) {
            // Случай 1: дядя красный — перекраска
            par->color = Black;
            unc->color = Black;
            gp->color = Red;
            nd = gp;
        } else {
            if (par == gp->left) {
                // Случай 2 (LR): nd — правый ребёнок
                if (nd == par->right) {
                    rotateLeft(root, par);
                    nd = par;
                    par = nd->parent;
                }
                // Случай 3 (LL): правый поворот
                rotateRight(root, gp);
                swap(par->color, gp->color);
                nd = par;
            } else {
                // Случай 2 (RL): nd — левый ребёнок
                if (nd == par->left) {
                    rotateRight(root, par);
                    nd = par;
                    par = nd->parent;
                }
                // Случай 3 (RR): левый поворот
                rotateLeft(root, gp);
                swap(par->color, gp->color);
                nd = par;
            }
        }
    }
    root->color = Black;
}
 
void insert(Node*& root, int val) {
    Node* nd = new Node(val);
    if (!root) {
        root = nd;
        root->color = Black;
        return;
    }
 
    Node* cur = root;
    Node* par = nullptr;
    while (cur) {
        par = cur;
        if (val < cur->data) cur = cur->left;
        else if (val > cur->data) cur = cur->right;
        else { delete nd; return; }
    }
 
    nd->parent = par;
    if (val < par->data) par->left = nd;
    else par->right = nd;
 
    fixInsert(root, nd);
}
 
Node* minimum(Node* nd) {
    while (nd && nd->left) nd = nd->left;
    return nd;
}
 
void transplant(Node*& root, Node* u, Node* v) {
    if (!u->parent) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if (v) v->parent = u->parent;
}
 
void erase(Node*& root, int val) {
    Node* z = root;
    while (z) {
        if (val < z->data) z = z->left;
        else if (val > z->data) z = z->right;
        else break;
    }
    if (!z) return;
 
    Node* y = z;
    Node* x = nullptr;
    Color yOriginalColor = y->color;
 
    if (!z->left) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (!z->right) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
 
        if (y->parent == z) {
            if (x) x->parent = y;
        } else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
}
 
void inorder(Node* nd) {
    if (!nd) return;
    inorder(nd->left);
    cout << nd->data << "(" << (nd->color == Red ? "R" : "B") << ") ";
    inorder(nd->right);
}
 
int main() {
    Node* root = nullptr;
    int arr[] = {7, 3, 18, 10, 22, 8, 11, 26};
    for (int v : arr) insert(root, v);
    cout << "Inorder: "; inorder(root); cout << endl;
 
    erase(root, 26);
    cout << "После удаления 26: "; inorder(root); cout << endl;
 
    erase(root, 7);
    cout << "После удаления 7 (корень): "; inorder(root); cout << endl;
 
    insert(root, 10);
    cout << "После вставки дубликата 10: "; inorder(root); cout << endl;
 
    