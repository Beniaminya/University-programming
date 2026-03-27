#include <iostream>
using namespace std;

struct Node {
    int KeyMin;
    int KeyMax;
    Node *Left;
    Node *Right;
}; 

Node* createNode(int l, int r) {
    Node* newNode = new Node;
    newNode->KeyMin = l;
    newNode->KeyMax = r;
    newNode->Left = nullptr;
    newNode->Right = nullptr;
    return newNode;
}

Node* buildTree(Node* node) {
    if (node->KeyMax - node->KeyMin == 1) return node;
    if (node->KeyMax - node->KeyMin > 1) {
        node->Left = buildTree(createNode(node->KeyMin, (node->KeyMax + node->KeyMin) / 2));
        node->Right = buildTree(createNode((node->KeyMax + node->KeyMin) / 2, node->KeyMax));
    }
    return node;
}

void preorder(Node* root) {
    if (!root) return;
    
    cout << root->KeyMin << ',' << root->KeyMax << ' ';
    preorder(root->Left);
    preorder(root->Right);
}

void valueCounter(Node* node, int& counter, int value){
    if (node){
        if ((value >= node->KeyMin) && (value <= node->KeyMax)){
            counter++;
            if (node->KeyMax - node->KeyMin > 1) {
                int mid = (node->KeyMax + node->KeyMin)/2;
                if (value <= mid) valueCounter(node->Left, counter, value);
                if (value >= mid) valueCounter(node->Right, counter, value);
            }
        }   
    }
    return;
}

int main() {
    int l, r;
    cout << "Введите через пробел начало и конец дерева: ";
    cin >> l >> r;
    if (l >= r) {
        cout << "Дерево отрезков не может быть построено.";
        return 0;
    }
    Node* tree = buildTree(createNode(l, r));
    preorder(tree);
    cout << endl;
    int search, counter = 0;
    cout << "Введите значение для подсчёта элемента: ";
    cin >> search;
    valueCounter(tree, counter, search);
    cout << "Значение " << search << " встречается столько раз: " << counter;
    return 0; 
}