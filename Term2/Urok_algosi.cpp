#include <iostream>
#include <algorithm>
using namespace std;

struct SegmentTreeNode{
    int l;
    int r;
    
    SegmentTreeNode* left;
    SegmentTreeNode* right;

    int max_value;
    int min_value;
    int sum;
    int odd;
    int even;

    SegmentTreeNode(int l, int r, int val): l(l), r(r), left(nullptr), right(nullptr), max_value(val), min_value(val),
    sum(val), odd(val%2 == 1), even(val%2 == 0){}
    SegmentTreeNode(int l, int r, SegmentTreeNode* leftChild, SegmentTreeNode* rightChild, int max_value, int min_value,
    int sum, int odd, int even): 
        l(l),
        r(r), 
        left(leftChild), 
        right(rightChild), 
        sum(leftChild-> sum + rightChild->sum), 
        max_value(max(leftChild->max_value, rightChild->max_value)),
        min_value(min(leftChild->min_value, rightChild->min_value)),
        odd(leftChild->odd + rightChild->odd ),
        even(leftChild->even + rightChild->even)
        {}
};