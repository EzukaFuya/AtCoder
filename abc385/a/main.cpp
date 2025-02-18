#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A, B, C;
    cin >> A >> B >> C;

    if (A == B  && B == C) cout << "Yes";
    else if ((A + B) == C) cout << "Yes";
    else if (A == (B + C)) cout << "Yes";
    else if ((A + C) == B) cout << "Yes";
    else cout << "No";

    cout << endl;

    return 0;
}