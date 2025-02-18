#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W, X;
    cin >> H >> W >>X;

    int P, Q;
    cin >> P >> Q;
    P--;
    Q--;

    vector<vector<ll>> S(H, vector<ll>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> S[i][j];
        }
    }

    vector<vector<bool>> visited(H, vector<bool>(W, false));
    visited[P][Q] = true;

    ll strength = S[P][Q];
    queue<pair<int, int>> grids;
    grids.push(pair{P, Q});

    vector<pair<int, int>> dir = {
        { 1,  0}, // 下
        {-1,  0}, // 上
        { 0,  1}, // 右
        { 0, -1}  // 左
    };

    while (!grids.empty()) {
        auto& pos = grids.front();
        grids.pop();
        // cout << S[pos.first + 1][pos.second] << (strength + X - 1) / X << endl;
        // cout << S[pos.first - 1][pos.second] << (strength + X - 1) / X << endl;
        // cout << S[pos.first][pos.second + 1] << (strength + X - 1) / X << endl;
        // cout << S[pos.first][pos.second - 1] << (strength + X - 1) / X << endl;

        for (auto& dire : dir) {
            int nx = pos.first + dire.first;
            int ny = pos.second + dire.second;

            if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
            if (visited[nx][ny]) continue;

            if (S[nx][ny] < (strength + X - 1) / X) {
                visited[nx][ny] = true;
                grids.push({nx, ny});
                strength += S[nx][ny];
            }
        }
    }
    cout << strength << endl;
    return 0;
}