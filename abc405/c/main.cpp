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
    vector<int> A(N);
    ll sum = 0;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        sum += A[i];
    }
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        ans += A[i] * (sum - A[i]);
    }
    ans /= 2;

    cout << ans << endl;


    return 0;
}