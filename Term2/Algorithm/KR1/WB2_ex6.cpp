#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

Node* createNode(int value){
    Node* newNode = new Node;
    newNode-> data = value;
    newNode-> next = nullptr;
    return newNode;
}

Node* createlist(int size){
    if (size == 0) return nullptr;
    cout << "Укажите элементы списка" << endl;
    int number;
    cin >> number;
    Node* head = createNode(number);
    cin >> number;
    Node* last = createNode(number);
    head->next = last;
    for (int i = 0; i < size-2; i++){
        cin >> number;
        Node* node = createNode(number);
        last -> next = node;
        last = node;
    }
    return head;
}

void printlist(Node* head){
    if (!head){
        cout << "nullptr";
        return;
    }
    Node* ptr = head;
    while (ptr){
        cout << ptr->data << " -> ";
        ptr = ptr->next;
    }
    cout << "nullptr";
}

int main(){
    int size;
    cout << "Укажите размер односвязанного списка ";
    cin >> size;
    if (size < 2) {
        cout << "Размер списка должен превышать 1";
        return 0;
    }
    Node* head = createlist(size);
    Node* chet_head = nullptr, *chet_tail = nullptr;
    Node* nechet_head = nullptr, *nechet_tail = nullptr;
    Node* cur = head;
    while(cur){
        Node* nxt = cur->next;
        cur->next = nullptr;
        if (cur->data%2 == 0){
            if (!chet_head) {chet_head = chet_tail = cur;}
            else {chet_tail->next = cur; chet_tail = cur;}
        }
        else{
            if (!nechet_head) {nechet_head = nechet_tail = cur;}
            else {nechet_tail->next = cur; nechet_tail = cur;}
        }
        cur = nxt;
    }
    Node* merged_head = nullptr;

    if (chet_head) {
        chet_tail->next = nechet_head;
        merged_head = chet_head;
    } else {
        merged_head = nechet_head;
    }

    printlist(merged_head);
}