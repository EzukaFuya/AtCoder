#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int X, Y;
    cin >> X >> Y;

    int counter = 0;
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            if ((i + j) >= X || (abs(i - j) >= Y) || abs(j - i) >= Y) {
                counter++;
            }
        }
    }
    double ans = counter / 36.0;
    cout << setprecision(10) << ans << endl;
    return 0;
}
