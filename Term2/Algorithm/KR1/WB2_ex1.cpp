#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    return newNode;
}

Node* createlist(const vector<int>& values) {
    int size = (int)values.size();
    if (size == 0) return nullptr;

    Node* head = createNode(values[0]);
    Node* last = head;

    for (int i = 1; i < size; i++) {
        Node* node = createNode(values[i]);
        last->next = node;
        last = node;
    }
    return head;
}

string checkErrors(Node* head, int size) {
    int counter = 0;
    Node* cur = head;

    while (cur) {
        counter++;
        if (counter > size) return "перескок";
        cur = cur->next;
    }

    if (counter < size) return "проскок";
    return "ок";
}

int main() {
    Node* head = nullptr;
    vector<int> values = {52, 42, 1488, 1337, 777, 228, 282};
    head = createlist(values);
    cout << checkErrors(head, (int)values.size()) << endl;
    head = createlist(values);
    Node* temp = head->next;
    Node* err = temp;
    temp = temp->next->next;
    err->next = temp;
    cout << checkErrors(head, (int)values.size()) << endl;
    head = createlist(values);
    temp = head->next;
    err = temp;
    temp = temp->next;
    temp->next = err;
    cout << checkErrors(head, (int)values.size()) << endl;
    return 0;
}