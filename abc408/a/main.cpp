#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, S;
    cin >> N >> S;
    vector<int> T(N);
    for (int i = 0; i < N; i++) {
        cin >> T[i];
    }

    for (int i = 1; i < N; i++) {
        if (T[i] - T[i-1] > S) {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}
