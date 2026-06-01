#include <iostream>
#include <vector>
using namespace std;

class BinaryHeap {
private:
    vector<int> heap;

    void heapUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;

            if (heap[index] > heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapDown(int index) {
        int size = heap.size();

        while (true) {
            int left = index * 2 + 1;
            int right = index * 2 + 2;
            int largest = index;

            if (left < size && heap[left] > heap[largest]) {
                largest = left;
            }

            if (right < size && heap[right] > heap[largest]) {
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

public:
    BinaryHeap() {

    }

    BinaryHeap(vector<int> arr) {
        heap = arr;

        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            heapDown(i);
        }
    }

    int get_max() {
        if (heap.empty()) {
            cout << "Куча пустая" << endl;
            return -1;
        }

        return heap[0];
    }

    int extract_max() {
        if (heap.empty()) {
            cout << "Куча пустая" << endl;
            return -1;
        }

        int maxElement = heap[0];

        heap[0] = heap[heap.size() - 1];
        heap.pop_back();

        if (!heap.empty()) {
            heapDown(0);
        }

        return maxElement;
    }

    void insert(int value) {
        heap.push_back(value);
        heapUp(heap.size() - 1);
    }

    void printHeap() {
        for (int x : heap) {
            cout << x << " ";
        }
        cout << endl;
    }
};

int main() {
    int num, el;

    cout << "Введите кол-во заданий: ";
    cin >> num;

    vector<int> arr;

    cout << "Введите приоритеты заданий через пробел" << endl;

    while (num != 0) {
        cin >> el;
        arr.push_back(el);
        num--;
    }

    BinaryHeap heap(arr);

    cout << "Максимальная двоичная куча: ";
    heap.printHeap();

    cout << "Максимальный приоритет: " << heap.get_max() << endl;

    cout << "Удалён максимальный приоритет: " << heap.extract_max() << endl;

    cout << "Куча после удаления максимума: ";
    heap.printHeap();

    cout << "Введите новый приоритет: ";
    cin >> el;

    heap.insert(el);

    cout << "Куча после добавления нового элемента: ";
    heap.printHeap();

    return 0;
}