#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

ll find_max_or_path(const Graph& graph, int start, int end, int length) {
    vector<bool> visited(length + 1, false);

    ll min_xor = (1LL << 60);

    function<void(int, ll)> dfs = [&](int vertex, ll current_xor) {
        visited[vertex] = true;

        if (vertex == end) {
            min_xor = min(min_xor, current_xor);
        }
        else {
            for (const auto& [next_vertex, weight] : graph[vertex]) {
                if (visited[next_vertex] == false) {
                    dfs(next_vertex, current_xor ^ weight);
                }
            }
        }
        visited[vertex] = false;
    };

    dfs(start, 0);

    return min_xor;
}

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    cin >> N >> M;

    Graph graph(N + 1);

    for (int i = 0; i < M; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;

        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    ll result = find_max_or_path(graph, 1, N, N);

    cout << result << endl;
    
    return 0;
}