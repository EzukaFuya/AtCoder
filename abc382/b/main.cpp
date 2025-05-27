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

    for (int i = N - 1; i >= 0; i--) {
        while (i >= 0 && S[i] == '.') {
            i--;
        }
        S[i] = '.';
        D--;
        if (D <= 0) break;
    }

    cout << S << endl;

    return 0;
}
