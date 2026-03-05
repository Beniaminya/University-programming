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
    }
    Node* ptr = head;
    while (ptr){
        cout << ptr->data << " -> ";
        ptr = ptr->next;
    }
    cout << "nullptr";
}


int main(){
    int size, X;
    cout << "Укажите размер односвязанного списка ";
    cin >> size;
    if (size < 2) {
        cout << "Размер списка должен превышать 1";
        return 0;
    }
    Node* head = createlist(size);
    // printlist(head);
    Node* head_less = nullptr;
    Node* tail_less = nullptr;
    Node* head_more = nullptr;
    Node* tail_more = nullptr;
    cout << "Введите число ";
    cin >> X;
    Node* lessHead = nullptr, *lessTail = nullptr;
    Node* geHead = nullptr, *geTail = nullptr;

    Node* cur = head;
    while (cur) {
        Node* nxt = cur->next;
        cur->next = nullptr;

        if (cur->data < X) {
            if (!lessHead) lessHead = lessTail = cur;
            else { lessTail->next = cur; lessTail = cur; }
        } else {
            if (!geHead) geHead = geTail = cur;
            else { geTail->next = cur; geTail = cur; }
        }

        cur = nxt;
    }
    cout << "Числа меньше заданного ";
    printlist(lessHead);
    cout << "\n";
    cout << "Числа большие заданного или равные ему ";
    printlist(geHead);
}