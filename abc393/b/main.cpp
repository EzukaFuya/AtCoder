#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;

    int counter = 0;
    for (int i = 0; i < S.length(); i++) {
        if (S[i] == 'A') {
            for (int j = 1; j <= (S.length() - i) / 2; j++) {
                if (S[i + j] == 'B' && S[i + 2 * j] == 'C') counter++;
            }
        }
    }
    cout << counter << endl;
    return 0;
}