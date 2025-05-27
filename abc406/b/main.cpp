#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    ll keta = 1;
    for (int i = 0;i < K; i++) {
        keta *= 10;
    }

    ll ans = 1;
    for (int i = 0; i < N; i++) {
        ll a;
        cin >> a;
        if (keta / a < ans) {
            ans = 1;
        }
        else {
            ans *= a;
            if (ans >= keta) {
                ans = 1;
            }
        }
    }
    cout << ans << endl;

    return 0;
}
