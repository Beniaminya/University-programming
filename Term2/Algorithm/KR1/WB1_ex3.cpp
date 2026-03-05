#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
int main(){
    int num;
    cin >> num;
    unordered_map<int,int> votes;
    unordered_set<int> arr;
    for (int i = 0; i < num; i++){
        int el;
        cin >> el;
        votes[el]++;
        arr.insert(el);
    }
    int max_vote = 0, max_num = 0;
    for (auto x: arr){
        int v = votes[x];
        if (v > max_vote){
            max_vote = v;
            max_num = x;
        }
    }
    if (max_vote > int(num/2)){
        cout << max_num;
    }
    else {
        cout << "Нет проекта, который считается лидером масс";
    }
}