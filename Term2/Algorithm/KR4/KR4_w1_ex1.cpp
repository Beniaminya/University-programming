#include <iostream>
#include <vector>
using namespace std;

vector<int> heap;

void headAppend(int index) {
    while (index > 0){
        int parent = (index - 1) / 2;
        if (heap[index] > heap[parent]){
            swap(heap[index], heap[parent]);
            index = parent;
        } else{break;}
    }
}

void insert(int value){
    heap.push_back(value);
    headAppend(heap.size()-1);
}

void printHeap(){
    for (int x: heap) cout << x << " ";
    cout << endl;
}

int main(){
    int num, el;
    cout << "Введите кол-во элементов ";
    cin >> num;
    cout << "Введите элементы через пробел" << endl;
    while (num != 0){
        cin >> el;
        insert(el);
        num--;
    }
    cout << "Максимальная двоичная куча: ";
    printHeap();
}