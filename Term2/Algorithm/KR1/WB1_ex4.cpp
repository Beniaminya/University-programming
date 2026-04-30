#include <iostream>
using namespace std;
int main(){
    int num,last, lmax = 1, l = 1;
    cin >> num;
    for (int i = 0; i < num; i++){
        int el;
        cin >> el;
        if (i == 0){
            last = el;
            continue;
        }
        if (el == last){
            l++;
            last = el;
        }
        else{
            if (l > lmax) lmax = l;
            last = el;
            l = 1;
        }
    }
    cout << lmax;
    return 0;
}