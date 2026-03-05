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

Node* mergeSorted(Node* a, Node* b){
    if (!a || !b) return nullptr;
    Node* result = nullptr;
    Node* last = nullptr;
    while (a && b){
        if (a-> data == b -> data){
            if(!result) {
                result = createNode(a->data);
                last = result;
            }
            else{
                last->next = createNode(a->data);
                last->next->prev = last;
                last = last -> next;
            }
            a = a->next;
            b = b->next;
        }
        else if (a->data < b->data){
            a = a->next;
        }
        else {
            b = b->next;
        }
    }
    return result;
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

int main(){
    Node* head1 = nullptr, *tail1 = nullptr;
    Node* head2 = nullptr, *tail2 = nullptr;
    int size1, size2, el;
    cout << "Enter first list size: ";
    cin >> size1;
    cout << "Enter second list size: ";
    cin >> size2;
    cout << "Enter the elements of the first list:" << endl;
    for (int i = 0; i < size1; i++){
        cin >> el;
        append(head1, tail1, el);
    }
    cout << "Enter the elements of the second list:" << endl;
    for (int i = 0; i < size2; i++){
        cin >> el;
        append(head2, tail2, el);
    }
    cout << "Merged list:" << endl;
    printlist(mergeSorted(head1, head2));
    return 0;
}