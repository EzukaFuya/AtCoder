#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double X;
    cin >> X;
    if (X >= 38.0) {
        cout << 1;
    }
    else if (X >= 37.5 && X < 38.0) {
        cout << 2;
    }
    else cout << 3;
    cout << endl;
    return 0;
}