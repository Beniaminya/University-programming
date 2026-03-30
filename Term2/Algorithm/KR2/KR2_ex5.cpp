#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct SegmentTreeNode {
    int l;
    int r;

    SegmentTreeNode* left;
    SegmentTreeNode* right;

    int max_value;
    int min_value;
    int sum;
    int odd;
    int even;

    SegmentTreeNode(int l, int r, int val)
        : l(l), r(r), left(nullptr), right(nullptr),
          max_value(val), min_value(val),
          sum(val), odd(val % 2 != 0), even(val % 2 == 0) {}

    SegmentTreeNode(int l, int r, SegmentTreeNode* leftChild, SegmentTreeNode* rightChild)
        : l(l), r(r),
          left(leftChild), right(rightChild),
          max_value(max(leftChild->max_value, rightChild->max_value)),
          min_value(min(leftChild->min_value, rightChild->min_value)),
          sum(leftChild->sum + rightChild->sum),
          odd(leftChild->odd + rightChild->odd),
          even(leftChild->even + rightChild->even) {}
};

SegmentTreeNode* buildTree(const vector<int>& arr, int l, int r) {
    if (l == r) {
        return new SegmentTreeNode(l, r, arr[l]);
    }
    int mid = (l + r) / 2;
    SegmentTreeNode* leftChild = buildTree(arr, l, mid);
    SegmentTreeNode* rightChild = buildTree(arr, mid + 1, r);
    return new SegmentTreeNode(l, r, leftChild, rightChild);
}

int queryMax(SegmentTreeNode* node, int ql, int qr) {
    if (node == nullptr) return -1000000000;
    if (qr < node->l || node->r < ql) return -1000000000;
    if (ql <= node->l && node->r <= qr) return node->max_value;
    return max(queryMax(node->left, ql, qr), queryMax(node->right, ql, qr));
}

int queryMin(SegmentTreeNode* node, int ql, int qr) {
    if (node == nullptr) return 1000000000;
    if (qr < node->l || node->r < ql) return 1000000000;
    if (ql <= node->l && node->r <= qr) return node->min_value;
    return min(queryMin(node->left, ql, qr), queryMin(node->right, ql, qr));
}

int queryEven(SegmentTreeNode* node, int ql, int qr) {
    if (node == nullptr) return 0;
    if (qr < node->l || node->r < ql) return 0;
    if (ql <= node->l && node->r <= qr) return node->even;
    return queryEven(node->left, ql, qr) + queryEven(node->right, ql, qr);
}

int queryOdd(SegmentTreeNode* node, int ql, int qr) {
    if (node == nullptr) return 0;
    if (qr < node->l || node->r < ql) return 0;
    if (ql <= node->l && node->r <= qr) return node->odd;
    return queryOdd(node->left, ql, qr) + queryOdd(node->right, ql, qr);
}

int querySum(SegmentTreeNode* node, int ql, int qr) {
    if (node == nullptr) return 0;
    if (qr < node->l || node->r < ql) return 0;
    if (ql <= node->l && node->r <= qr) return node->sum;
    return querySum(node->left, ql, qr) + querySum(node->right, ql, qr);
}

void deleteTree(SegmentTreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    cout << "Введите через пробел левую и правую границу массива: ";
    int l, r;
    cin >> l >> r;

    if (r < l) {
        cout << "Дерево инициализировано некорректно";
        return 0;
    }

    vector<int> arr;
    int el;
    for (int i = 0; i <= r - l; i++) {
        cin >> el;
        arr.push_back(el);
    }

    SegmentTreeNode* tree = buildTree(arr, 0, arr.size() - 1);

    int ql, qr;
    cout << "Введите интервал (через пробел), для которого будут выполняться операции: ";
    cin >> ql >> qr;

    if (qr < ql) {
        cout << "Интервал инициализирован некорректно";
        deleteTree(tree);
        return 0;
    }

    ql -= l;
    qr -= l;

    if (ql < 0 || qr >= arr.size()) {
        cout << "Интервал выходит за границы массива";
        deleteTree(tree);
        return 0;
    }

    cout << "Максимальный элемент: " << queryMax(tree, ql, qr) << endl;
    cout << "Минимальный элемент: " << queryMin(tree, ql, qr) << endl;
    cout << "Сумма элементов на интервале: " << querySum(tree, ql, qr) << endl;
    cout << "Количество чётных элементов: " << queryEven(tree, ql, qr) << endl;
    cout << "Количество нечётных элементов: " << queryOdd(tree, ql, qr) << endl;

    deleteTree(tree);
}