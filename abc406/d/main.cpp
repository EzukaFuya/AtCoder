#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W, N;
    cin >> H >> W >>N;
    vector<vector<int>> x_ids(H+1);
    vector<vector<int>> y_ids(W+1);
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        x_ids[x].push_back(i);
        y_ids[y].push_back(i);
    }

    int Q;
    cin >> Q;
    set<int> del_ids;
    for (int i = 0; i < Q; i++) {
        int que;
        cin >> que;
        int ans = 0;

        if (que == 1) {
            int x;
            cin >> x;
            vector<int> ids = x_ids[x];
            x_ids[x] = {};
            ans = ids.size();
            for (int i = 0; i < ids.size(); i++) {
                if (del_ids.count(ids[i]) == 1) {
                    ans--;
                }
                else {
                    del_ids.insert(ids[i]);
                }
            }
            cout << ans << endl;
        }
        else if (que == 2) {
            int y;
            cin >> y;
            vector<int> ids = y_ids[y];
            y_ids[y] = {};
            ans = ids.size();
            for (int i = 0; i < ids.size(); i++) {
                if (del_ids.count(ids[i]) == 1) {
                    ans--;
                }
                else {
                    del_ids.insert(ids[i]);
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}
