#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;

    int last_num = S[0] - '0';
    int diff_num = 0;
    for (int i = 1; i < S.length(); i++) {
        int num = S[i] - '0';
        if (last_num < num) last_num += 10;
        diff_num += last_num - num;
        last_num = num;
    }
    diff_num += last_num;
    cout << diff_num + S.length() << endl;
    return 0;
}
