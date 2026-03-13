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

int findBetter(Node* root, int value){
    int better = root->data;
    while (root) {
        if (abs(root-> data - value) <= abs(value - better)){
            better = min(better, root->data);
        }
        if (root -> data > value){
            root = root->left;
        }
        else{
            root = root->right;
        }    
    }
    return better;
}

int main(){
    Node* root = nullptr;
    int num, el, value;
    cin >> num;
    if (num == 0){
        cout << "Can't find the closest mark, because none exists";
        return 0;
    }
    for (int i = 0; i < num; i++){
        cin >> el;
        root = addNode(root, el);
    }
    cin >> value;
    cout << "The closest value is " << findBetter(root, value);
}