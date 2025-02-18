#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A1, A2, A3;
    cin >> A1 >> A2 >> A3;

    if (A1 * A2 == A3 || A1 * A3 == A2 || A2 * A3 == A1) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}