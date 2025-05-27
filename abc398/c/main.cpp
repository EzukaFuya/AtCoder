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
    
    map <int, int> mp;
    map <int, int> pr;

    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        mp[a]++;
        if (mp[a] == 1) pr[a] = i;
    }

    int max_num = 0;
    int max_per = -1;
    for (auto &pair : mp) {
        if (pair.second == 1) {
            if (pair.first > max_num) {
                max_num = pair.first;
            }
        }
    }

    if (max_num != 0) {
        cout << pr[max_num] + 1 << endl;
        return 0;
    }
    else {
        cout << "-1" << endl;
        return 0;
    }
    return 0;
}