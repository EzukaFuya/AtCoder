#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;

    queue<int> que;
    bool is_out = false;

    for(int i = 0; i < Q; i++) {
        int q;
        cin >> q;
        if (q == 1) {
            int x;
            cin >> x;
            que.push(x);
        }
        else {
            int num = que.front();
            que.pop();
            cout << num << endl;
            is_out = true;
        }
    }
    if (!is_out) {
        cout << endl;
    }

    return 0;
}