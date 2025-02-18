/* 基本テンプレート */
queue<T> q;                    // 探索キュー
vector<vector<bool>> visited;  // 訪問管理
// または
vector<vector<int>> distance;  // 距離管理（-1は未訪問を表す）

// 初期化
q.push(開始位置);
visited[開始位置] = true;  // または distance[開始位置] = 0

// 探索
while (!q.empty()) {
    auto current = q.front();
    q.pop();
    
    for (次の位置を全て試す) {
        if (範囲内 && !visited[次の位置]) {
            visited[次の位置] = true;
            q.push(次の位置);
        }
    }
}