#include <iostream>
using namespace std;

struct Node {
    int data;
    int priority;
    Node* next;
};

Node* head = nullptr;

bool isEmpty() {
    return head == nullptr;
}

void push(int data, int priority) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = nullptr;
    if (head == nullptr || priority < head->priority) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr && current->next->priority <= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

int pop() {
    if (head == nullptr) {
        cout << "Очередь пустая" << endl;
        return -1;
    }
    Node* temp = head;
    int value = head->data;
    head = head->next;
    delete temp;
    return value;
}

int front() {
    if (head == nullptr) {
        cout << "Очередь пустая" << endl;
        return -1;
    }
    return head->data;
}

void printQueue() {
    if (head == nullptr) {
        cout << "Очередь пустая" << endl;
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " " << current->priority << endl;
        current = current->next;
    }
}

void clearQueue() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    int num, data, priority;
    cout << "Введите кол-во элементов: ";
    cin >> num;
    cout << "Введите значение и приоритет" << endl;
    while (num != 0) {
        cin >> data >> priority;
        push(data, priority);
        num--;
    }
    cout << "Очередь с приоритетом:" << endl;
    printQueue();
    cout << "Первый элемент: " << front() << endl;
    cout << "Удалён элемент: " << pop() << endl;
    cout << "Очередь после удаления:" << endl;
    printQueue();
    clearQueue();
    return 0;
}