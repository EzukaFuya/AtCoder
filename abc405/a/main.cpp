#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R, X;
    cin >> R >> X;

    if (X == 1 && (R < 3000 && R >= 1600)) cout << "Yes" << endl;
    else if (X == 1) cout << "No" << endl;
    else if (X == 2 && (R <2400 && R >= 1200)) cout << "Yes" << endl;
    else if (X == 2) cout << "No" << endl;
    return 0;
}