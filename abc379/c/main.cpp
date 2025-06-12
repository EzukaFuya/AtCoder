#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N, M;
    cin >> N >> M;
    
    vector<ll> X(M), A(M);
    
    for (int i = 0; i < M; i++) {
        cin >> X[i];
    }
    
    ll total_stones = 0;
    for (int i = 0; i < M; i++) {
        cin >> A[i];
        total_stones += A[i];
    }
    
    if (total_stones != N) {
        cout << -1 << endl;
        return 0;
    }
    
    vector<pair<ll, ll>> stones(M);
    for (int i = 0; i < M; i++) {
        stones[i] = {X[i], A[i]};
    }
    sort(stones.begin(), stones.end());
    
    ll total_cost = 0;
    ll target_pos = 0;
    
    for (int i = 0; i < M; i++) {
        if (target_pos < stones[i].first - 1) {
            cout << -1 << endl;
            return 0;
        }
        target_pos += stones[i].second;
        total_cost += stones[i].first * stones[i].second;
    }
    if (target_pos != N) {
        cout << -1 << endl;
        return 0;
    }
    
    cout << (N * (N + 1)) / 2 - total_cost << endl;
    return 0;
}
