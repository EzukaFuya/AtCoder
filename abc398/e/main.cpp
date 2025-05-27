#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    vector<vector<int>> G(N);
    vector<vector<bool>> has_edge(N, vector<bool>(N, false));
    
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
        has_edge[u][v] = has_edge[v][u] = true;
    }
    
    // 二部グラフの色分け
    vector<int> color(N, -1);
    queue<int> q;
    color[0] = 0;
    q.push(0);
    
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int nv : G[v]) {
            if (color[nv] == -1) {
                color[nv] = 1 - color[v];
                q.push(nv);
            }
        }
    }
    
    // 部集合のサイズを計算
    int sizeA = 0, sizeB = 0;
    for (int i = 0; i < N; i++) {
        if (color[i] == 0) sizeA++;
        else sizeB++;
    }
    
    // 追加可能な辺の総数: A*B - (N-1)
    // 現在の辺はすべて異なる集合間の辺であり、その数はN-1
    int potential_edges = sizeA * sizeB - (N-1);
    
    // 異なる色の頂点ペアをリスト化
    vector<pair<int, int>> possible_moves;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // 異なる色の頂点間で、まだ辺がない場合
            if (color[i] != color[j] && !has_edge[i][j]) {
                possible_moves.push_back({i, j});
            }
        }
    }
    
    // 先手/後手の決定
    bool is_my_turn;
    if (potential_edges % 2 == 1) {
        cout << "First" << endl;
        is_my_turn = true;
    } else {
        cout << "Second" << endl;
        is_my_turn = false;
    }
    
    // ゲームの進行
    while (true) {
        if (is_my_turn) {
            // 自分の手番
            bool moved = false;
            
            // 異なる色の頂点間で辺を選ぶ
            for (auto& move : possible_moves) {
                int u = move.first;
                int v = move.second;
                
                if (!has_edge[u][v]) {
                    int i = u + 1;
                    int j = v + 1;
                    cout << i << " " << j << endl;
                    
                    has_edge[u][v] = has_edge[v][u] = true;
                    moved = true;
                    break;
                }
            }
            
            is_my_turn = false;
        } else {
            // 相手の手番
            int i, j;
            cin >> i >> j;
            
            // ゲーム終了
            if (i == -1 && j == -1) {
                break;
            }
            
            // 相手の手を反映
            i--; j--;
            has_edge[i][j] = has_edge[j][i] = true;
            
            is_my_turn = true;
        }
    }
    
    return 0;
}