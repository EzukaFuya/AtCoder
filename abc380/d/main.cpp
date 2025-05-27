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
        ll index = K % length_S;
        bool is_reversed = (K / length_S) % 2 == 1;

        char current_char = S[index];
        if (is_reversed) {
            isupper(current_char) ? current_char = tolower(current_char) : current_char = toupper(current_char);
        }
        cout << current_char << " ";
    }

    cout << endl;

    return 0;
}