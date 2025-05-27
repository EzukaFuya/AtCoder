#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N, K;
    cin >> N >> K;
    
    const ll MOD = 1000000000; // 10^9
    
    if (N < K) {
        cout << 1 << endl;
        return 0;
    }
    
    if (N == K) {
        cout << K % MOD << endl;
        return 0;
    }
    
    // Initialize queue with first K values (all 1s)
    queue<ll> que;
    ll sum = K; // Sum of first K elements
    
    for (ll i = 0; i < K; i++) {
        que.push(1);
    }
    
    // Calculate remaining values
    for (ll i = K; i < N; i++) {
        ll oldest = que.front();
        que.pop();
        
        // New value is the sum of previous K values
        ll newest = sum;
        que.push(newest);
        
        // Update sum: add newest, remove oldest
        sum = (sum + newest - oldest) % MOD;
        if (sum < 0) sum += MOD; // Ensure positive modulo
    }
    
    cout << sum% MOD << endl;
    return 0;
}