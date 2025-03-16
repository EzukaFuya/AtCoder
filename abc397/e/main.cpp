#include <bits/stdc++.h>
using namespace std;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, K;
    cin >> N >> K;
    
    int total_nodes = N * K;
    vector<vector<int>> T(total_nodes);
    
    // 木の辺を読み込む
    for (int i = 0; i < total_nodes - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // 0-indexedに変換
        T[u].push_back(v);
        T[v].push_back(u);
    }
    
    vector<int> size(total_nodes, 1); // 各頂点を根とする部分木のサイズ
    
    // DFSで木を探索（非再帰版）
    stack<tuple<int, int, int>> st;
    st.push({0, -1, 0}); // (頂点, 親, 状態)
    
    while (!st.empty()) {
        auto [v, p, state] = st.top();
        st.pop();
        
        if (state == 0) {
            // 子を調べる前の状態
            st.push({v, p, 1}); // 子を調べた後の状態をスタックに積む
            
            for (int u : T[v]) {
                if (u != p) {
                    st.push({u, v, 0});
                }
            }
        } else {
            // 子を調べた後の状態
            int child_count = 0; // 生きている子の数
            
            for (int u : T[v]) {
                if (u != p) {
                    size[v] += size[u];
                    if (size[u] > 0) {
                        child_count++;
                    }
                }
            }
            
            // 部分木のサイズ > K の場合はパスに分解できない
            if (size[v] > K) {
                cout << "No" << endl;
                return 0;
            }
            
            // 子が3つ以上ある場合はパスにならない
            if (child_count >= 3) {
                cout << "No" << endl;
                return 0;
            }
            
            // 部分木のサイズ < K だが子が2つ以上ある場合もパスにならない
            if (size[v] < K && child_count >= 2) {
                cout << "No" << endl;
                return 0;
            }
            
            // ちょうどK頂点の部分木が見つかった場合は取り除く
            if (size[v] == K) {
                size[v] = 0;
            }
        }
    }
    
    cout << "Yes" << endl;
    return 0;
}