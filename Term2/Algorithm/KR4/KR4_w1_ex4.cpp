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

void insert(int length) {
    heap.push_back(length);
    siftUp(heap.size() - 1);
}

int extractMin() {
    if (heap.empty()) {
        cout << "Куча пустая" << endl;
        return -1;
    }

    int minElement = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();

    if (!heap.empty()) {
        siftDown(0);
    }

    return minElement;
}

void printHeap() {
    for (int x : heap) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    int n, length;
    cout << "Введите количество канатов: ";
    cin >> n;
    cout << "Введите длины канатов через пробел" << endl;
    while (n != 0) {
        cin >> length;
        insert(length);
        n--;
    }
    int totalCost = 0;
    cout << endl;
    cout << "Порядок связывания канатов:" << endl;
    while (heap.size() > 1) {
        int first = extractMin();
        int second = extractMin();
        int newRope = first + second;
        cout << first << " + " << second << " = " << newRope << endl;
        totalCost += newRope;
        insert(newRope);
    }

    cout << endl;
    cout << "Суммарные затраты: " << totalCost << endl;

    return 0;
}