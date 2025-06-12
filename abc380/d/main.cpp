#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    ll Q;
    cin >> S >> Q;

    ll length_S = S.length();
    for (int i = 0; i < Q; i++) {
        ll K;
        cin >> K;

        K--; // 0-indexed
        ll num_division = K / length_S; // number of full divisions
        ll index_in_S = K % length_S; // index in S
        char c = S[index_in_S];
        int count = 0;
        while (num_division) {
            count += num_division & 1;
            num_division >>= 1;
        }
        if (count % 2 == 1) {
            if (isupper(c)) {
                c = tolower(c);
            } else {
                c = toupper(c);
            }
        }

        cout << c;
        if (i != Q - 1) cout << " ";
    }

    cout << endl;

    return 0;
}