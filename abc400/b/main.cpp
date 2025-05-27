#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >>  N >> M;

    ll X = 1;
    for (int i = 1; i <= M; i++) {
        ll N_i = 1;
        for (int j = 1; j <= i; j++) {
            N_i *= N;
        }
        X += N_i;
        if (X > 1e9) {
            cout << "inf" << endl;
            return 0;
        }
    }

    cout << X << endl;
    return 0;
}