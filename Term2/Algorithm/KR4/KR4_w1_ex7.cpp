#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Task {
    string name;
    int priority;
};

vector<Task> heap;

void siftUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].priority > heap[parent].priority) {
            swap(heap[index], heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void siftDown(int index) {
    int size = heap.size();
    while (true) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int largest = index;
        if (left < size && heap[left].priority > heap[largest].priority) {
            largest = left;
        }
        if (right < size && heap[right].priority > heap[largest].priority) {
            largest = right;
        }
        if (largest != index) {
            swap(heap[index], heap[largest]);
            index = largest;
        } else {
            break;
        }
    }
}

void insertTask(string name, int priority) {
    Task task;
    task.name = name;
    task.priority = priority;
    heap.push_back(task);
    siftUp(heap.size() - 1);
}

Task extractMax() {
    Task task;
    task.name = "";
    task.priority = -1;
    if (heap.empty()) {
        cout << "Список дел пустой" << endl;
        return task;
    }
    task = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    if (!heap.empty()) {
        siftDown(0);
    }
    return task;
}

void printTasks() {
    if (heap.empty()) {
        cout << "Список дел пустой" << endl;
        return;
    }
    for (int i = 0; i < heap.size(); i++) {
        cout << i + 1 << ". " << heap[i].name << " " << heap[i].priority << endl;
    }
}

int findTask(string name) {
    for (int i = 0; i < heap.size(); i++) {
        if (heap[i].name == name) {
            return i;
        }
    }
    return -1;
}

void editTask(string name) {
    int index = findTask(name);
    if (index == -1) {
        cout << "Такого задания нет" << endl;
        return;
    }

    string newName;
    int newPriority;

    cout << "Введите новое название задания: ";
    cin >> newName;

    cout << "Введите новый приоритет: ";
    cin >> newPriority;

    int oldPriority = heap[index].priority;

    heap[index].name = newName;
    heap[index].priority = newPriority;

    if (newPriority > oldPriority) {
        siftUp(index);
    } else {
        siftDown(index);
    }

    cout << "Задание изменено" << endl;
}

int main() {
    int choice;
    string name;
    int priority;

    while (true) {
        cout << endl;
        cout << "1 - добавить задание" << endl;
        cout << "2 - выполнить самое важное задание" << endl;
        cout << "3 - вывести список дел" << endl;
        cout << "4 - изменить задание" << endl;
        cout << "0 - выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Введите название задания одним словом: ";
            cin >> name;
            cout << "Введите приоритет: ";
            cin >> priority;
            insertTask(name, priority);
            cout << "Задание добавлено" << endl;
        } else if (choice == 2) {
            Task task = extractMax();
            if (task.priority != -1) {
                cout << "Выполнено задание: " << task.name << " с приоритетом " << task.priority << endl;
            }
        } else if (choice == 3) {
            cout << "Список дел:" << endl;
            printTasks();
        } else if (choice == 4) {
            cout << "Введите название задания, которое хотите изменить: ";
            cin >> name;
            editTask(name);
        } else if (choice == 0) {
            break;
        } else {
            cout << "Нет такого действия" << endl;
        }
    }

    return 0;
}