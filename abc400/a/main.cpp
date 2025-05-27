#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A;
    cin >>  A;
    if (400 % A == 0) {
        cout << 400 / A << endl;
    }
    else {
        cout <<  -1 << endl;
    }
    return 0;
}