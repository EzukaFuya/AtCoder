#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    vector<string> T(H);
    for (int i = 0; i < H; i++) {
        cin >> S[i];
    }

    pair<int, int> exit = {-1, -1};
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (S[i][j] == 'E') {
                exit = {i, j};
            } 
        }
    }
    if (exit.first == -1 && exit.second == -1) {
        T = S;
        for (int i = 0; i < H; i++) {
            cout << T[i] << endl;
        }
        return 0;
    }

    // search exit for BFS
    queue<pair<int, int>> que;
    vector<vector<bool>> visited(H, vector<bool>(W, false));
    vector<pair<int, int>> dist = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    que.push({0, 0});

    while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();
        for (auto [dx, dy] : dist) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
            if (visited[nx][ny]) continue;
            if (S[nx][ny] == '#') continue;
            if (S[nx][ny] == 'E') {
                T = S;
                continue;
            }
            visited[x][y] = true;
            que.push({nx, ny});
            if (dx == 0 && dy == 1) {
                S[x][y] = 'v';
            } else if (dx == 0 && dy == -1) {
                S[x][y] = '^';
            } else if (dx == 1 && dy == 0) {
                S[x][y] = '>';
            } else if (dx == -1 && dy == 0) {
                S[x][y] = '<';
            }
        }
    }

    for (int i = 0; i < H; i++) {
        cout << T[i] << endl;
    }
    return 0;
}