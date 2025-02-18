#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int K;
    string S, T;
    cin >> K >> S >> T;

    if (S == T) {
        cout << "Yes" << endl;
        return 0;
    }

    int ns = S.length();
    int nt = T.length();

    if (abs(ns - nt) > 1) {
        cout << "No" << endl;
        return 0;
    }

    int offset_s = 0;
    int offset_t = 0;
    int count = 0;

    for (int i = 0; i < min(ns, nt); i++) {

        if ((i + offset_s) >= ns) break;
        if ((i + offset_t) >= nt) break;

        if (S[i + offset_s] != T[i + offset_t]) {
            if (ns < nt) offset_t++;
            else if (ns > nt) offset_s++;
            count++;
        }
    }

    if (count > 1) cout << "No" << endl;
    else cout << "Yes" << endl;
    return 0;
}