#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A;
    cin >> A;
    if (A >= 200 && A < 300) {
        cout << "Success" << endl;
        return 0;
    }
    else {
        cout << "Failure" << endl;
        return 0;
    }
    return 0;
}