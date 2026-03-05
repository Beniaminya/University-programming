#include <iostream>
#include <vector>
using namespace std;

class MyStack{
    public:

    vector<int> stack;

    void push(int n){
        stack.push_back(n);
    } 

    void pop(){
        if (!stack.empty()) {
            cout << stack.back() << endl;
            stack.pop_back();
        }
    }

    void back(){
        if (!stack.empty()) {
        cout << stack.back() << endl;
    }
    }

    void size(){
        cout << stack.size() << endl;
    }

    void clear(){
        stack.clear();
    }
};

#include "main1_5.cpp"