#include <iostream>
using namespace std;

enum Color { Red, Black };

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Color color;    
    Node(int value, Color color) : data(value), left(nullptr), right(nullptr), parent(nullptr), color(color) {}
};


Node* insert(int value, Color color, Node* root){
    
    Node* newNode = new Node(value,color);
    if (root == nullptr) return newNode;

    Node* cur = root;
    Node* parent = nullptr;

    while (cur) {
        parent = cur;
        if (value < cur->data) cur = cur->left;
        else if (value > cur->data) cur = cur->right;
        else {
            delete newNode;
            return root;
        }
    }

    newNode->parent = parent;
    if (value < parent->data) parent->left = newNode;
    else parent->right = newNode;

    return root;
}

bool checkRoot(Node* root){
    return root->color == Black;
}

bool checkRedNodes(Node* root){
    if (!root) return true;
    if (root->color == Red){
        bool leftnode = root->left && root->left->color == Red;
        bool rightnode = root->right && root->right->color == Red;
        if (leftnode || rightnode) return false;
    }
    return checkRedNodes(root->left) && checkRedNodes(root->right);
}

int blackHeight(Node* n) {
    if (!n) return 1;
    int lh = blackHeight(n->left);
    int rh = blackHeight(n->right);
    if (lh == -1 || rh == -1 || lh != rh) return -1;
    return lh + (n->color == Black ? 1 : 0);
}

int main() {
    Node* tree1 = nullptr;
    tree1 = insert(13, Black, tree1);
    tree1 = insert(8,  Red,   tree1);
    tree1 = insert(17, Black, tree1);
    tree1 = insert(1,  Black, tree1);
    tree1 = insert(11, Black, tree1);
    tree1 = insert(15, Red,   tree1);
    tree1 = insert(25, Red,   tree1);

    bool p2_t1 = checkRoot(tree1);
    bool p4_t1 = checkRedNodes(tree1);
    bool p5_t1 = blackHeight(tree1) != -1;

    cout << "Дерево 1" << endl;
    cout << (p2_t1 && p4_t1 && p5_t1 ? "Является красно-чёрным" : "Не является красно-чёрным") << endl;

    Node* tree2 = nullptr;
    tree2 = insert(10, Red,   tree2);
    tree2 = insert(5,  Red,   tree2);
    tree2 = insert(20, Black, tree2);
    tree2 = insert(3,  Black, tree2);
    tree2 = insert(7,  Black, tree2);

    bool p2_t2 = checkRoot(tree2);
    bool p4_t2 = checkRedNodes(tree2);
    bool p5_t2 = blackHeight(tree2) != -1;

    cout << "\nДерево 2" << endl;
    cout << (p2_t2 && p4_t2 && p5_t2 ? "Является красно-чёрным" : "Не является красно-чёрным") << endl;

    return 0;
}