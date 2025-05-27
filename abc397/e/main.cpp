#include <bits/stdc++.h>
using namespace std;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, K;
    cin >> N >> K;  // N個のK頂点パスに分解できるか判定（全体でN*K頂点）
    
    int total_nodes = N * K;
    vector<vector<int>> T(total_nodes);  // 隣接リスト形式の木
    
    // 木の辺を読み込む
    for (int i = 0; i < total_nodes - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;  // 0-indexedに変換
        T[u].push_back(v);
        T[v].push_back(u);  // 無向グラフなので両方向に追加
    }
    
    vector<int> size(total_nodes, 1);  // 各頂点を根とする部分木のサイズ（初期値は1=自分自身）
    
    // DFSで木を探索（非再帰版）
    stack<tuple<int, int, int>> st;  // (頂点, 親, 状態)
    st.push({0, -1, 0});  // 頂点0を根として探索開始
    
    while (!st.empty()) {
        auto [v, p, state] = st.top();  // 頂点、親、状態を取得
        st.pop();
        
        if (state == 0) {
            // 下りフェーズ：子を調べる前の状態
            st.push({v, p, 1});  // 同じ頂点を状態1でスタックに戻す
            
            for (int u : T[v]) {
                if (u != p) {  // 親でない隣接頂点のみ処理（木なので）
                    st.push({u, v, 0});  // 子を状態0でスタックに追加
                }
            }
        } else {
            // 上りフェーズ：子を調べた後の状態
            int child_count = 0;  // 生きている子の数
            
            for (int u : T[v]) {
                if (u != p) {
                    size[v] += size[u];  // 子の部分木サイズを加算
                    if (size[u] > 0) {  // 取り除かれていない子をカウント
                        child_count++;
                    }
                }
            }
            
            // 判定条件1: サイズがKを超える部分木は分解不可能
            if (size[v] > K) {
                cout << "No" << endl;
                return 0;
            }
            
            // 判定条件2: 子が3つ以上あるとパスにならない
            if (child_count >= 3) {
                cout << "No" << endl;
                return 0;
            }
            
            // 判定条件3: サイズがK未満で子が2つ以上あるとパスにならない
            if (size[v] < K && child_count >= 2) {
                cout << "No" << endl;
                return 0;
            }
            
            // K頂点のパスを発見したら取り除く
            if (size[v] == K) {
                size[v] = 0;  // 部分木を取り除いたことを表すためにサイズを0に
            }
        }
    }
    
    // すべての判定をパスしたら分解可能
    cout << "Yes" << endl;
    return 0;
}