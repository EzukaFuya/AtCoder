#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int H, W, K, path_num;

void dfs(vector<string> &S, int x, int y, int l, vector<vector<bool>> &visited) {
    if (l == K) {
        path_num++;
        return;
    }

    if ((x + 1) < H && S[x+1][y] != '#') {
        if (visited[x+1][y] == false) {
            visited[x+1][y] = true;
            dfs(S, x+1, y, l+1, visited);
            visited[x+1][y] = false;
        }
    }
    if ((x - 1) >= 0 && S[x-1][y] != '#') {
        if (visited[x-1][y] == false) {
            visited[x-1][y] = true;
            dfs(S, x-1, y, l+1, visited);
            visited[x-1][y] = false;
        }
    }
    if ((y + 1) < W && S[x][y+1] != '#') {
        if (visited[x][y+1] == false) {
            visited[x][y+1] = true;
            dfs(S, x, y+1, l+1, visited);
            visited[x][y+1] = false;
        }
    }
    if ((y - 1) >= 0 && S[x][y-1] != '#') {
        if (visited[x][y-1] == false) {
            visited[x][y-1] = true;
            dfs(S, x, y-1, l+1, visited);
            visited[x][y-1] = false;
        }
    }
}

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> H >> W >> K;

    queue<pair<int, int>> que_start_point;

    vector<string> S(H);
    for (int i = 0; i < H; i++) {
        cin >> S[i];
        for (int j = 0; j < W; j++) {
            if (S[i][j] != '#') {
                que_start_point.push({i, j});
            }
        }
    }

    vector<vector<int>> dir ={{1, 0}, {-1, 0}, {0, 1}, {0, 1}};
    while (!que_start_point.empty()) {
        auto start_pos = que_start_point.front();
        que_start_point.pop();

        vector<vector<bool>> visited(H, vector<bool>(W, false));
        visited[start_pos.first][start_pos.second] = true;
        dfs(S, start_pos.first, start_pos.second, 0, visited);
    }

    cout << path_num << endl;

    return 0;
}
