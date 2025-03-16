#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<pair<int,string>> S(N);
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        S[i] = {s.length(), s};
    }

    sort(S.begin(), S.end());

    for (int i = 0; i < N; i++) {
        cout << S[i].second;
    }
    cout << endl;
    return 0;
}