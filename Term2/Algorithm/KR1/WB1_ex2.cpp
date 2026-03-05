#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

bool half(const vector<int>& arr, int summa) {
    if (summa % 2 != 0) return false;
    int target = summa / 2;

    const int MAX_SUM = 10000;
    if (target > MAX_SUM) return false;

    bitset<MAX_SUM + 1> dp;
    dp[0] = 1;

    for (int x : arr) {
        dp |= (dp << x);
    }

    return dp[target];
}

int main() {
    int num, el;
    int summa = 0;

    cin >> num;
    vector<int> arr;
    arr.reserve(num);

    for (int i = 0; i < num; i++) {
        cin >> el;
        if (el < 0) { 
            cout << "NO";
            return 0;
        }
        summa += el;
        arr.push_back(el);
    }

    cout << (half(arr, summa) ? "YES" : "NO");
    return 0;
}
