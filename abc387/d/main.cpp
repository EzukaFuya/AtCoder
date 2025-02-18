#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   
   // 入力
   int H, W;
   cin >> H >> W;
   
   vector<string> grid(H);
   int start_i = 0, start_j = 0;
   int goal_i = 0, goal_j = 0;
   
   // グリッドの読み込みとS,G位置の特定
   for (int i = 0; i < H; i++) {
       cin >> grid[i];
       for (int j = 0; j < W; j++) {
           if (grid[i][j] == 'S') {
               start_i = i, start_j = j;
           } else if (grid[i][j] == 'G') {
               goal_i = i, goal_j = j;
           }
       }
   }
   
   // 水平・垂直の移動パターン定義
   vector<vector<pair<int, int>>> moves(2);
   moves[0] = {{0, 1}, {0, -1}};  // 水平方向
   moves[1] = {{1, 0}, {-1, 0}};  // 垂直方向
   
   int ans = INF;
   
   // 水平→垂直、垂直→水平の2パターンで試す
   for (int pattern = 0; pattern < 2; pattern++) {
       // 距離テーブルの初期化
       vector<vector<int>> dist(H, vector<int>(W, INF));
       dist[start_i][start_j] = 0;
       
       // BFS
       queue<pair<int, int>> que;
       que.push({start_i, start_j});
       
       while (!que.empty()) {
           auto [curr_i, curr_j] = que.front();
           que.pop();
           
           // マスの座標和とパターンから移動方向を決定
           for (auto [di, dj] : moves[(curr_i + curr_j + pattern) & 1]) {
               int ni = curr_i + di;
               int nj = curr_j + dj;
               
               // 範囲チェック
               if (ni < 0 || ni >= H || nj < 0 || nj >= W) continue;
               // 壁チェック
               if (grid[ni][nj] == '#') continue;
               // 未訪問チェック
               if (dist[ni][nj] != INF) continue;
               
               dist[ni][nj] = dist[curr_i][curr_j] + 1;
               que.push({ni, nj});
           }
       }
       
       ans = min(ans, dist[goal_i][goal_j]);
   }
   
   cout << (ans == INF ? -1 : ans) << endl;
   
   return 0;
}