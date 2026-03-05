#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_set>
using namespace std;
int main(){
    cout << "Ввод:" << '\n';
    int num,el;
    cin >> num;
    unordered_set<int> given;
    unordered_set<int> got;
    for (int i = 0; i < num; i++){
        cin >> el;
        given.insert(el);
    }
    string s;
    cin.ignore();
    getline(cin, s);
    stringstream ss(s);
    while (ss >> el) got.insert(int(el));
    // for (auto el: given) cout << el << ' ';
    // cout << '\n';
    // for (auto el: got) cout << el << ' ';
    cout << "Вывод:" << '\n';
    for (auto el: given){
        if (!got.count(el)){
            cout << el << ' ';
        }
    }
}