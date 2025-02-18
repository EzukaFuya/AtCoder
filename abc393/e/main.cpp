#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    int M = 0;  // 最大値
    for (auto& a : A) {
        cin >> a;
        M = max(M, a);
    }

    // s[n]: 値nの出現回数
    vector<int> s(M + 1), t(M + 1), u(M + 1);
    for (auto& a : A) s[a]++;

    // t[d]: dの倍数の出現回数
    for (int d = 1; d <= M; d++) {
        for (int n = d; n <= M; n += d) {
            t[d] += s[n];
        }
    }

    // u[n]: 値nに対する答え（最大のGCD）
    for (int d = 1; d <= M; d++) {
        if (t[d] < K) continue;
        for (int n = d; n <= M; n += d) {
            u[n] = max(u[n], d);
        }
    }

    // 各クエリに対する答えを出力
    for (auto& a : A) {
        cout << u[a] << "\n";
    }

    return 0;
}