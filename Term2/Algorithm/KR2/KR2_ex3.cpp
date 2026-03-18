#include <iostream>
#include <vector>
using namespace std;

struct Node{
    string name;
    vector<string> numbers;
    Node* right;
    Node* left;
};

Node* searchNode(Node* root, string name) {
    if (!root) return nullptr;
    if (root->name == name) return root;
    if (name < root->name) return searchNode(root->left, name);
    else return searchNode(root->right, name);
}

Node* createNode(string name, string number){
    Node* newNode = new Node;
    newNode->name = name;
    newNode->numbers.push_back(number);
    newNode->right = nullptr;
    newNode->left = nullptr;
    return newNode;
}

Node* addNode(Node* root, string name, string number){
    if (!root){
        return createNode(name, number);
    }
    if (name > root->name){
        root->right = addNode(root->right, name, number);
    }
    else{
        root->left = addNode(root->left, name, number);
    }
    return root;
}

Node* addNumber(Node* root, string name, string number){
    Node* find = searchNode(root, name);
    if (find){
        find->numbers.push_back(number);
        return root;
    }
    else{
        return addNode(root, name, number);
    }
}

void preorder(Node* root) {
    if (!root) return;

    cout << root->name << ": ";
    for (auto number: root->numbers){
        cout << number << " ";
    }
    cout << endl;
    preorder(root->left);
    preorder(root->right);
}

Node* findMax(Node* root) {
    while (root->right != nullptr) {
        root = root->right;
    }
    return root;
}

Node* deleteNode(Node* root, string name) {
    if (root == nullptr) {
        return nullptr;
    }

    if (name < root->name) {
        root->left = deleteNode(root->left, name);
    }
    else if (name > root->name) {
        root->right = deleteNode(root->right, name);
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
        root->name = maxLeft->name;
        root->numbers = maxLeft->numbers;
        root->left = deleteNode(root->left, maxLeft->name);
    }
    return root;
}

int main(){
    Node* book = new Node;
    cout << "Введите количество контактов ";
    int c;
    string name, number;
    cin >> c;
    cout << "Введите имя человека без пробелов и через пробел номер" << endl;
    for (long long i = 0; i < c; i++){
        cin >> name >> number;
        book = addNumber(book, name, number);
    }
    cout << "Книга контактов:" << endl;
    preorder(book);
    string search, del;
    cout << "Введите имя человека, номер(а) которого хотите найти ";
    cin >> search;
    Node* find = searchNode(book, search);
    if (find){
        cout << "Номер(а) " << search << ":" << endl;
        for (auto number: find->numbers){
            cout << number << endl;
        }
    }
    else{
        cout << "Контакт " << search << " не найден" << endl;
    }
    cout << "Введите имя человека, которого хотите удалить ";
    cin >> del;
    Node * to_del = searchNode(book, del);
    if (to_del){
        book = deleteNode(book, name);
        cout << "Контакт " << del << " удалён" << endl;
    }
    else{
        cout << "Контакт " << del << " не найден" << endl;
    }
    cout << "Книга контактов:" << endl;
    preorder(book);
}