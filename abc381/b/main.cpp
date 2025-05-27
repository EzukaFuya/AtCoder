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
    if (S.length() % 2 == 1) {
        cout << "No" << endl;
        return 0;
    }

    set<int> set_S;
    for (int i = 0;i < S.length() - 1; i++) {
        if (i % 2 == 0) {
            if (S[i] != S[i + 1]) {
                cout << "No" << endl;
                return 0;
            }
            if(set_S.find(S[i]) != set_S.end()) {
                cout << "No" << endl;
                return 0;
            }
            set_S.insert(S[i]);
        }
        else {
            if (S[i] == S[i + 1]) {
                cout << "No" << endl;
                return 0;
            }
        }
    }
    cout << "Yes" << endl;
    return 0;
}
