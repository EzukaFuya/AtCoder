#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    string S;
    bool is_login = false;
    int error_count = 0;
    for (int i = 0; i < N; i++) {
        cin >> S;
        if (S == "login") {
            is_login = true;
        }
        else if (!is_login && S == "private") {
            error_count++;
        }
        else if (S == "logout") {
            is_login = false;
        }
    }

    cout << error_count << endl;
    return 0;
}