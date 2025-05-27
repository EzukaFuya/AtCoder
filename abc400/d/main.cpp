#include <bits/stdc++.h>
using namespace std;

// 4方向の移動ベクトル（上、下、左、右）
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

int main() {
    // 入力
    int H, W;
    cin >> H >> W;
    
    vector<string> grid(H);
    for (int i = 0; i < H; i++) {
        cin >> grid[i];
    }
    
    int A, B, C, D;
    cin >> A >> B >> C >> D;
    
    // 0-indexedに変換
    A--; B--; C--; D--;
    
    // 各マスへの最小前蹴り回数を保存
    vector<vector<int>> dist(H, vector<int>(W, H * W)); // 十分大きな値で初期化
    dist[A][B] = 0; // 開始位置
    
    // 01-BFSのための両端キュー
    deque<int> que;
    que.push_front(A * W + B); // 位置を1次元に変換して保存
    
    while (!que.empty()) {
        int pos = que.front();
        que.pop_front();
        
        // 位置を2次元に戻す
        int x = pos / W;
        int y = pos % W;
        
        // 目的地に到達したら終了
        if (x == C && y == D) {
            cout << dist[C][D] << endl;
            return 0;
        }
        
        // 4方向を調べる
        for (int dir = 0; dir < 4; dir++) {
            bool wall_encountered = false;
            
            // 1マス目と2マス目を調べる
            for (int step = 1; step <= 2; step++) {
                int nx = x + dx[dir] * step;
                int ny = y + dy[dir] * step;
                
                // グリッド外ならループを抜ける
                if (nx < 0 || nx >= H || ny < 0 || ny >= W) 
                    break;
                
                // 壁があればフラグを立てる
                if (grid[nx][ny] == '#') 
                    wall_encountered = true;
                
                // 壁に遭遇していない場合（道を移動中）
                if (!wall_encountered) {
                    // 1マス目への移動はコスト0
                    if (step == 1) {
                        if (dist[nx][ny] > dist[x][y]) {
                            dist[nx][ny] = dist[x][y];
                            que.push_front(nx * W + ny); // コスト0はデックの前に
                        }
                    }
                }
                // 壁に遭遇した場合（前蹴りが必要）
                else {
                    if (dist[nx][ny] > dist[x][y] + 1) {
                        dist[nx][ny] = dist[x][y] + 1;
                        que.push_back(nx * W + ny); // コスト1はデックの後ろに
                    }
                }
            }
        }
    }
    
    // 到達できない場合（実際にはこのケースは問題設定上ない）
    cout << -1 << endl;
    return 0;
}