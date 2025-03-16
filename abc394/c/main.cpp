#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;

    int i = 0;
    while (i < S.length()) {
        i++;
        if (S[i - 1] == 'W' && S[i] == 'A') {
            S[i - 1] = 'A';
            S[i]     = 'C';
            i -= 2;
            if (i < 0) i = 0;
        }
    }
    cout << S << endl;
    return 0;
}