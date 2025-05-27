#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, D;
    cin >> N >> D;

    string S;
    cin >> S;

    int cookys_count = 0;
    for (int i = 0; i < N; i++) {
        if (S[i] == '@') cookys_count++;
    }

    int ans = 0;
    ans = max(cookys_count - D, 0);
    cout << N - ans << endl;
    return 0;
}