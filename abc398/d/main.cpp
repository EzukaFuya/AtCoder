#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, R, C;
    cin >> N >> R >> C;

    string S;
    cin >> S;

    set<pair<ll, ll>> st;
    st.insert({0, 0});
    pair<ll, ll> pos = {0, 0};
    pair<ll, ll> tar = {R, C};

    for (int i = 0; i < N; i++) {
        if (S[i] == 'N') {
            tar.first++;
            pos.first++;
        }
        else if (S[i] == 'S') {
            tar.first--;
            pos.first--;
        }
        else if (S[i] == 'E') {
            tar.second--;
            pos.second--;
        }
        else if (S[i] == 'W') {
            tar.second++;
            pos.second++;
        }

        st.insert(pos);

        if (st.find(tar) != st.end()) {
            cout << 1;
        }
        else {
            cout << 0;
        }
    }
    cout << endl;
    return 0;
}