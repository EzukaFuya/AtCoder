#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    cin >> N;
    
    ll l, r, m, ans = 0;
    ll inf = 1e9;

    l = 0;
    r = inf;

    while ((l + 1) < r) {
        m = (l + r) / 2;
        if ((m * m * 2) <= N) l = m;
        else r = m;
    }
    ans += l;

    l = 0; r = inf;
    while ((l + 1) < r) {
        m = (l + r) / 2;
        if ((m * m * 4) <= N) l = m;
        else r = m;
    }

    ans += l;
    cout << ans << endl;

    return 0;
}