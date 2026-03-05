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
    if (size == 1) return head;
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

Node* sumlist(Node*& head1, Node*& head2){
    if (head1 == nullptr && head2 == nullptr) return nullptr;
    Node* result = nullptr;
    Node* tail = nullptr;
    int cur = 0;
    while (head1 != nullptr || head2 != nullptr || cur != 0){
        int summa = cur;
        if (head1 != nullptr){
            summa += head1->data;
            head1 = head1->next;
        }
        if (head2 != nullptr){
            summa += head2->data;
            head2 = head2->next;
        }
        cur = summa/10;
        Node* newNode = createNode(summa%10);
        if (result == nullptr){
            result = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            tail = newNode;
        }
    }
    return result;
}

Node* reverse(Node* head) {
    Node* prev = nullptr;
    Node* cur = head;
    while (cur) {
        Node* nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    return prev;
}

int main(){
    int size1, size2;
    cout << "Укажите размер первого списка ";
    cin >> size1;
    Node* head1 = createlist(size1);
    cout << "Укажите размер второго списка ";
    cin >> size2;
    Node* head2 = createlist(size2);
    Node* res = reverse(sumlist(head1,head2));
    printlist(res);
}