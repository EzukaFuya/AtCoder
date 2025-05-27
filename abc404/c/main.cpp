#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

vector<bool> visited;

int dfs(vector<vector<int>>& graph, int node) {
    visited[node] = true;
    
    for (auto& neighbor : graph[node]) {
        if (visited[neighbor] == false) {
            dfs(graph, neighbor);
        }
    }
    return 0;
}

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<vector<int>> graph(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    visited.resize(N, false);
    dfs(graph, 0);

    int edge_counter = 0;
    for (int i = 0; i < N; i++) {
        if (visited[i] == true) {
            edge_counter++;
        }
    }

    for (int i = 0; i < N; i++) {
        if (graph[i].size() != 2) {
            cout << "No" << endl;
            return 0;
        }
    }

    if (edge_counter == N && N ==M ) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}