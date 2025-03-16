#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e18;

// グラフの型定義
using Graph = vector<vector<int>>;              // 隣接リスト（重みなし）
using WeightedGraph = vector<vector<pair<int, ll>>>; // 隣接リスト（重み付き）

// Union-Find（DSU: Disjoint Set Union）
class UnionFind {
private:
    vector<int> parent, size;
public:
    UnionFind(int n) : parent(n, -1), size(n, 1) {}
    
    // 根を求める
    int find(int x) {
        if (parent[x] == -1) return x;
        return parent[x] = find(parent[x]); // 経路圧縮
    }
    
    // xとyのグループを統合
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        
        // サイズが小さい方を大きい方に統合（union by size）
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        return true;
    }
    
    // xとyが同じグループに属するか
    bool same(int x, int y) { return find(x) == find(y); }
    
    // xのグループのサイズ
    int get_size(int x) { return size[find(x)]; }
};

// 深さ優先探索（DFS）
vector<bool> seen;
void dfs(const Graph &G, int v) {
    seen[v] = true;
    for (int nv : G[v]) {
        if (seen[nv]) continue;
        dfs(G, nv);
    }
}

// 幅優先探索（BFS）
vector<int> bfs(const Graph &G, int start) {
    int n = G.size();
    vector<int> dist(n, -1); // -1は未訪問
    queue<int> que;
    dist[start] = 0;
    que.push(start);
    
    while (!que.empty()) {
        int v = que.front(); que.pop();
        for (int nv : G[v]) {
            if (dist[nv] != -1) continue; // 訪問済み
            dist[nv] = dist[v] + 1;
            que.push(nv);
        }
    }
    return dist;
}

// ダイクストラ法（単一始点最短経路）
vector<ll> dijkstra(const WeightedGraph &G, int start) {
    int n = G.size();
    vector<ll> dist(n, LINF);
    dist[start] = 0;
    
    // {距離, 頂点}のペアを格納する優先度付きキュー
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> que;
    que.push({0, start});
    
    while (!que.empty()) {
        auto [d, v] = que.top(); que.pop();
        if (dist[v] < d) continue; // 既に最短距離が確定している場合
        
        for (auto [nv, weight] : G[v]) {
            if (dist[nv] > dist[v] + weight) {
                dist[nv] = dist[v] + weight;
                que.push({dist[nv], nv});
            }
        }
    }
    return dist;
}

// ベルマン・フォード法（負の重みがある場合の単一始点最短経路）
// 戻り値: {最短距離, 負閉路検出フラグ}
pair<vector<ll>, bool> bellman_ford(const WeightedGraph &G, int start) {
    int n = G.size();
    vector<ll> dist(n, LINF);
    dist[start] = 0;
    bool negative_cycle = false;
    
    // 辺のリストを構築
    vector<tuple<int, int, ll>> edges;
    for (int v = 0; v < n; ++v) {
        for (auto [nv, weight] : G[v]) {
            edges.emplace_back(v, nv, weight);
        }
    }
    
    // 最短経路の計算
    for (int i = 0; i < n; ++i) {
        for (auto [from, to, weight] : edges) {
            if (dist[from] == LINF) continue;
            if (dist[to] > dist[from] + weight) {
                dist[to] = dist[from] + weight;
                // n回目の更新があれば負閉路が存在
                if (i == n - 1) negative_cycle = true;
            }
        }
    }
    
    return {dist, negative_cycle};
}

// ワーシャル・フロイド法（全点対最短経路）
vector<vector<ll>> warshall_floyd(const WeightedGraph &G) {
    int n = G.size();
    vector<vector<ll>> dist(n, vector<ll>(n, LINF));
    
    // 初期化
    for (int v = 0; v < n; ++v) {
        dist[v][v] = 0;
        for (auto [nv, weight] : G[v]) {
            dist[v][nv] = weight;
        }
    }
    
    // 全点対最短経路の計算
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] == LINF || dist[k][j] == LINF) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    
    return dist;
}

// クラスカル法（最小全域木）
ll kruskal(vector<tuple<ll, int, int>> &edges, int n) {
    // 辺を重みの昇順にソート
    sort(edges.begin(), edges.end());
    
    UnionFind uf(n);
    ll total_weight = 0;
    
    for (auto [weight, u, v] : edges) {
        if (!uf.same(u, v)) {
            uf.unite(u, v);
            total_weight += weight;
        }
    }
    
    return total_weight;
}

// トポロジカルソート（DAG: 有向非巡回グラフ）
vector<int> topological_sort(const Graph &G) {
    int n = G.size();
    vector<int> indegree(n, 0); // 入次数
    for (int v = 0; v < n; ++v) {
        for (int nv : G[v]) {
            ++indegree[nv];
        }
    }
    
    queue<int> que;
    for (int v = 0; v < n; ++v) {
        if (indegree[v] == 0) que.push(v);
    }
    
    vector<int> order;
    while (!que.empty()) {
        int v = que.front(); que.pop();
        order.push_back(v);
        
        for (int nv : G[v]) {
            --indegree[nv];
            if (indegree[nv] == 0) que.push(nv);
        }
    }
    
    // orderのサイズがnでなければ閉路が存在
    if (order.size() != n) order.clear();
    return order;
}

// 強連結成分分解（SCC: Strongly Connected Components）
class SCC {
private:
    int n;
    Graph G, rG; // 元のグラフと辺を逆向きにしたグラフ
    vector<int> vs; // 帰りがけ順の並び
    vector<bool> used; // 訪問フラグ
    vector<int> comp; // 強連結成分の番号
    
    // 1回目のDFS
    void dfs(int v) {
        used[v] = true;
        for (int nv : G[v]) {
            if (!used[nv]) dfs(nv);
        }
        vs.push_back(v);
    }
    
    // 2回目のDFS
    void rdfs(int v, int k) {
        used[v] = true;
        comp[v] = k;
        for (int nv : rG[v]) {
            if (!used[nv]) rdfs(nv, k);
        }
    }
    
public:
    SCC(const Graph &graph) : n(graph.size()), G(graph), rG(n), comp(n, -1) {
        // 辺を逆向きにしたグラフを構築
        for (int v = 0; v < n; ++v) {
            for (int nv : G[v]) {
                rG[nv].push_back(v);
            }
        }
    }
    
    // 強連結成分分解を実行
    int build() {
        used.assign(n, false);
        vs.clear();
        
        // 1回目のDFS
        for (int v = 0; v < n; ++v) {
            if (!used[v]) dfs(v);
        }
        
        // 2回目のDFS
        used.assign(n, false);
        int k = 0;
        reverse(vs.begin(), vs.end());
        for (int v : vs) {
            if (!used[v]) rdfs(v, k++);
        }
        
        return k; // 強連結成分の総数
    }
    
    // 強連結成分のグラフを構築
    Graph build_scc_graph() {
        int k = build();
        Graph scc_graph(k);
        
        for (int v = 0; v < n; ++v) {
            for (int nv : G[v]) {
                if (comp[v] != comp[nv]) {
                    scc_graph[comp[v]].push_back(comp[nv]);
                }
            }
        }
        
        return scc_graph;
    }
    
    // 頂点vの属する強連結成分の番号
    int operator[](int v) const {
        return comp[v];
    }
};

// LCA（最小共通祖先）
class LCA {
private:
    vector<vector<int>> parent; // parent[k][v] := 頂点vの2^k個上の親
    vector<int> depth;
    int root, n, log_n;
    
public:
    LCA(const Graph &G, int root = 0) : root(root) {
        n = G.size();
        log_n = 1;
        while ((1 << log_n) < n) ++log_n;
        
        parent.assign(log_n, vector<int>(n, -1));
        depth.assign(n, -1);
        
        dfs(G, root, -1, 0);
        
        // ダブリング
        for (int k = 0; k + 1 < log_n; ++k) {
            for (int v = 0; v < n; ++v) {
                if (parent[k][v] != -1) {
                    parent[k + 1][v] = parent[k][parent[k][v]];
                }
            }
        }
    }
    
    // 深さを計算するDFS
    void dfs(const Graph &G, int v, int p, int d) {
        parent[0][v] = p;
        depth[v] = d;
        
        for (int nv : G[v]) {
            if (nv != p) dfs(G, nv, v, d + 1);
        }
    }
    
    // 頂点uと頂点vのLCAを求める
    int query(int u, int v) {
        // uとvの深さを揃える
        if (depth[u] < depth[v]) swap(u, v);
        
        // uを2^k個上に遡らせる
        for (int k = 0; k < log_n; ++k) {
            if ((depth[u] - depth[v]) >> k & 1) {
                u = parent[k][u];
            }
        }
        
        if (u == v) return u;
        
        // 二分探索でLCAを求める
        for (int k = log_n - 1; k >= 0; --k) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        
        return parent[0][u];
    }
    
    // 頂点uと頂点vの距離
    int distance(int u, int v) {
        int lca = query(u, v);
        return depth[u] + depth[v] - 2 * depth[lca];
    }
};

// XOR最小パスを求めるDFS（単純パス）
ll min_xor_path(const WeightedGraph &G, int start, int goal) {
    int n = G.size();
    vector<bool> visited(n, false);
    ll min_xor = LINF;
    
    function<void(int, ll)> dfs = [&](int v, ll current_xor) {
        visited[v] = true;
        
        if (v == goal) {
            min_xor = min(min_xor, current_xor);
        } else {
            for (auto [nv, weight] : G[v]) {
                if (!visited[nv]) {
                    dfs(nv, current_xor ^ weight);
                }
            }
        }
        
        visited[v] = false; // バックトラック
    };
    
    dfs(start, 0);
    return min_xor;
}

// メイン関数（使用例）
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    // 重み付きグラフの作成
    WeightedGraph G(n + 1); // 1-indexed
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        
        // 無向グラフ
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    
    // 例：頂点1から頂点nまでの最小XORを求める
    ll result = min_xor_path(G, 1, n);
    cout << result << endl;
    
    return 0;
}