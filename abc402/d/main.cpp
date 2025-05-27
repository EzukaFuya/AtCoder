#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;  

    vector<pair<int, int>> A(M);
    for (int i = 0; i < M; i++) {
        cin >> A[i].first >> A[i].second;
    }

    vector<ll> count(N, 0);
    for (int i = 0; i < M; i++) {
        int x, y;
        x = A[i].first;
        y = A[i].second;
        count[(x + y) % N]++;
    }
    
    ll ans = 0;
    ll total_pairs = (ll)M * (M - 1) / 2; //all pairs
    for (int i = 0; i < N; i++) {
        ans += count[i] * (count[i] - 1) / 2;
    }

    ans = total_pairs - ans;
    cout << ans << endl;    

    return 0;
}