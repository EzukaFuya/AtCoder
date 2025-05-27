#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int N;
        cin >> N;
        
        vector<ll> A(2 * N);
        for (int i = 0; i < 2 * N; i++) {
            if (i != 2 * N) cin >> A[i];
        }
        
        ll ans = 0;
        priority_queue<ll> pq;

        for (int i = 0; i < N; i++) {
            if (i == 0) {
                pq.push(A[0]);
            }
            else {
                pq.push(A[2 * i]);
                pq.push(A[2 * i - 1]);
            }
            ll max_val = pq.top();
            pq.pop();
            ans += max_val;
        }

        cout << ans << endl;
    }
    
    return 0;
}
