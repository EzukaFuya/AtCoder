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
    T = S;

    vector<pair<int, int>> exit;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (S[i][j] == 'E') {
                exit.push_back({i, j});
            } 
        }
    }
    if (exit.empty()) {
        for (int i = 0; i < H; i++) {
            cout << T[i] << endl;
        }
        return 0;
    }

    // BFS from exit position to all other cells
    vector<vector<int>> dist(H, vector<int>(W, -1));
    queue<pair<int, int>> que;
    vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    vector<char> arrows = {'>', '<', 'v', '^'};
    
    for (auto& exit_pos : exit) {
        que.push(exit_pos);
        dist[exit_pos.first][exit_pos.second] = 0;
    }
    
    while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();
        
        for (int d = 0; d < 4; d++) {
            int dx = dirs[d].first;
            int dy = dirs[d].second;
            int nx = x + dx;
            int ny = y + dy;
            
            if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
            if (S[nx][ny] == '#') continue;
            if (dist[nx][ny] != -1) continue;
            
            dist[nx][ny] = dist[x][y] + 1;
            que.push({nx, ny});
        }
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (T[i][j] == '.' && dist[i][j] > 0) { // Skip exit and unreachable cells
                for (int d = 0; d < 4; d++) {
                    int dx = dirs[d].first;
                    int dy = dirs[d].second;
                    int nx = i + dx;
                    int ny = j + dy;
                    
                    if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
                    if (dist[nx][ny] != dist[i][j] - 1) continue;
                    
                    T[i][j] = arrows[d];
                    break; // Found the direction, no need to check others
                }
            }
        }
    }
    
    // Output the result
    for (int i = 0; i < H; i++) {
        cout << T[i] << endl;
    }
    
    return 0;
}
