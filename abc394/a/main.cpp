#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;

    for (int i = 0; i < S.length(); i++) {
        if(S[i] == '2') {
            cout << '2';
        }
    }
    cout << endl;
    return 0;
}