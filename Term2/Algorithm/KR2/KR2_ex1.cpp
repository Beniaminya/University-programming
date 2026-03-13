#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int value){
    Node* newNode = new Node;
    newNode->data = value;
    newNode->right = nullptr;
    newNode->left = nullptr;
    return newNode;
}

Node* addNode(Node* root, int value){
    if (!root){
        return createNode(value);
    }
    if (value > root->data){
        root->right = addNode(root->right, value);
    }
    else{
        root->left = addNode(root->left,value);
    }
    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

int depthTree(Node* root) {
    if (root == nullptr)
        return 0;

    int leftHeight = depthTree(root->left);
    int rightHeight = depthTree(root->right);

    return max(leftHeight, rightHeight) + 1;
}

// Node* searchNode(Node* root, int value){
//     if (!root) return nullptr;
//     if (root->data == value) return root;
//     Node* leftNode = searchNode(root->left, value);
//     Node* rightNode = searchNode(root->right, value);
//     if (leftNode) return leftNode;
//     if (rightNode) return rightNode;
//     return nullptr;
// }

Node* searchNode(Node* root, int value) {
    if (!root) return nullptr;

    if (root->data == value)
        return root;

    if (value < root->data)
        return searchNode(root->left, value);
    else
        return searchNode(root->right, value);
}

Node* findMax(Node* root) {
    while (root->right != nullptr) {
        root = root->right;
    }
    return root;
}

Node* deleteNode(Node* root, int value) {
    if (root == nullptr) {
        return nullptr;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    }
    else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }

        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* maxLeft = findMax(root->left);
        root->data = maxLeft->data;
        root->left = deleteNode(root->left, maxLeft->data);
    }
    return root;
}

int main(){
    Node* root = nullptr;
    int el_to_del = 0, el_to_find = 0;
    for (int i = 0; i < 8; i++){
        int el = rand()%100;
        root = addNode(root,el);
        if (i == 7){
            el_to_del = el;
        }
        if (i == 4){
            el_to_find = el;
        }   
    }
    cout << "Прямой обход дерева:" << endl;
    preorder(root);
    cout << endl;
    cout << "Обратный обход дерева:" << endl;
    postorder(root);
    cout << endl;
    cout << "Симметричный обход дерева:" << endl;
    inorder(root);
    cout << endl;
    cout << "Глубина дерева: " << depthTree(root) << endl;
    cout << "Элемент который надо найти: " << el_to_find << ". Найденный элемент - " << searchNode(root, el_to_find)->data << endl;
    cout << "Элемент который надо удалить " << el_to_del << endl;
    cout << "Список после удаления" << endl;
    root = deleteNode(root,el_to_del);
    preorder(root); 
}

