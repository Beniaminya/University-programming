#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
    Node* prev;
};

void append(Node*& head, int num){
    Node* node = new Node{num, nullptr, nullptr};

    if (!head){
        head = node;
        node->next = node;
        node->prev = node;
        return;
    }

    Node* end = head->prev;

    end->next = node;
    node->prev = end;

    node->next = head;
    head->prev = node;
}

void del(Node*& head, int value) {
    if (!head) return;

    Node* cur = head;
    do {
        if (cur->data == value) {
            if (cur->next == cur) {
                delete cur;
                head = nullptr;
                return;
            }

            Node* left = cur->prev;
            Node* right = cur->next;

            left->next = right;
            right->prev = left;

            if (cur == head) head = right;

            delete cur;
            return;
        }
        cur = cur->next;
    } while (cur != head);
}

void printlist(Node* head) {
    if (!head) { cout << "empty\n"; return; }

    Node* cur = head;
    do {
        cout << cur->data << " -> ";
        cur = cur->next;
    } while (cur != head);

    cout << "цикл завершён\n";
}

int main(){
    Node* head = nullptr;

    int size, el, dop_el, del_el;
    cout << "Введите размер списка ";
    cin >> size;

    cout << "Введите элементы списка\n";
    for (int i = 0; i < size; i++){
        cin >> el;
        append(head, el);
    }

    printlist(head);

    cout << "Введите элемент, который хотите добавить в конец списка ";
    cin >> dop_el;
    append(head, dop_el);
    printlist(head);

    cout << "Введите элемент, который хотите удалить из списка ";
    cin >> del_el;
    del(head, del_el);
    printlist(head);
}
