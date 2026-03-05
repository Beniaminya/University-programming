#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* prev;
    Node* next;
};

Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

void append(Node*& head, Node*& tail, int num){
    Node* newNode = createNode(num);
    if (!head){
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

void insertBefore(Node*& head, Node*& tail, int pos, int value) {
    if (!head) return;

    Node* cur = head;
    while (cur && cur->data != pos) cur = cur->next;
    if (!cur) return;

    Node* newNode = createNode(value);
    newNode->next = cur;
    newNode->prev = cur->prev;

    if (cur->prev) cur->prev->next = newNode;
    else head = newNode;

    cur->prev = newNode;
}

void del(Node*& head, Node*& tail, int value) {
    Node* cur = head;
    while (cur) {
        Node* nxt = cur->next;

        if (cur->data == value) {
            if (cur->prev) cur->prev->next = cur->next;
            else head = cur->next;

            if (cur->next) cur->next->prev = cur->prev;
            else tail = cur->prev;

            delete cur;
        }

        cur = nxt;
    }
}

int getSize(Node* head){
    int counter = 0;
    for (Node* cur = head; cur; cur = cur->next) counter++;
    return counter;
}

Node* reverse(Node* head) {
    Node* cur = head;
    Node* newHead = nullptr;
    while (cur) {
        Node* nxt = cur->next;
        cur->next = cur->prev;
        cur->prev = nxt;
        newHead = cur;
        cur = nxt;
    }
    return newHead;
}

void printlist(Node* head){
    if (!head){
        cout << "nullptr\n";
        return;
    }
    Node* ptr = head;
    while (ptr){
        cout << ptr->data << " -> ";
        ptr = ptr->next;
    }
    cout << "nullptr\n";
}

bool is_palindrome(Node* head, Node* tail){
    if (!head) return true;

    Node* start = head;
    Node* end = tail;

    while (start != end && start->prev != end) {
        if (start->data != end->data) return false;
        start = start->next;
        end = end->prev;
    }
    return true;
}

int main(){
    Node* head = nullptr;
    Node* tail = nullptr;
    append(head, tail, 1);
    append(head, tail, 2);
    append(head, tail, 3);
    append(head, tail, 5);
    printlist(head);
    getSize(head);
    insertBefore(head,tail,1,0);
    insertBefore(head,tail,2,2);
    printlist(head);
    del(head,tail, 2);
    printlist(head);
    printlist(reverse(head));
    Node* head1 = nullptr; 
    Node* tail1 = nullptr;
    append(head1, tail1, 1);
    append(head1, tail1, 2);
    append(head1, tail1, 1);
    if (is_palindrome(head1, tail1)){
        cout << "Список ";
        printlist(head1);
        cout << "Является палиндромом";
    }
    else{
        printlist(head1);
        cout << "НЕ является палиндромом";
    }
    return 0;
}

