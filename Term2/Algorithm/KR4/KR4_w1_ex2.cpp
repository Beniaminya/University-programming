#include <iostream>
#include <vector>
using namespace std;

vector<int> heap; 


void siftUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index] < heap[parent]) {
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
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        
        if (left < size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }
        
        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

void insert(int deadline) {
    heap.push_back(deadline);
    siftUp(heap.size() - 1);
    cout << "Работа со временем сдачи " << deadline << " добавлена" << endl;
}

int extractMin() {
    if (heap.empty()) {
        cout << "Нет работ для проверки" << endl;
        return -1;
    }
    
    int minDeadline = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    
    if (!heap.empty()) {
        siftDown(0);
    }
    
    cout << "Проверяется работа со временем сдачи " << minDeadline << endl;
    return minDeadline;
}

int peek() {
    if (heap.empty()) {
        cout << "Нет работ" << endl;
        return -1;
    }
    return heap[0];
}

void printHeap() {
    if (heap.empty()) {
        cout << "Куча пуста" << endl;
        return;
    }
    cout << "Текущие работы (время сдачи): ";
    for (int x : heap) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    int choice, value;
    
    while (true) {
        cout << "\n1. Добавить работу" << endl;
        cout << "2. Извлечь работу для проверки (самая ранняя)" << endl;
        cout << "3. Посмотреть следующую работу" << endl;
        cout << "4. Вывести все работы" << endl;
        cout << "5. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Введите время сдачи: ";
                cin >> value;
                insert(value);
                break;
            case 2:
                extractMin();
                break;
            case 3:
                value = peek();
                if (value != -1) {
                    cout << "Следующая работа (самая ранняя): " << value << endl;
                }
                break;
            case 4:
                printHeap();
                break;
            case 5:
                cout << "Программа завершена" << endl;
                return 0;
            default:
                cout << "Неверный ввод" << endl;
        }
    }
}