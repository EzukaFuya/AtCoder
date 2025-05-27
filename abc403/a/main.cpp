#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    ll sum = 0;
    for (int i = 0; i < N; i++) {
        
        int x;
        cin >> x;
        if (i % 2 == 0) {
            sum += x;
        }
    }

    cout << sum << endl;
    return 0;
}