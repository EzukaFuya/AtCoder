#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;
    for (int i = 0; i < S.size(); i++) {
        if (isupper(S[i])) {
            cout << S[i];
        }
    }
    cout << endl;
    return 0;
}