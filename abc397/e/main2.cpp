#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    int t_nodes = N * K;
    vector<vector<int>> T(t_nodes);

    for (int i = 0; i < t_nodes - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        T[u].push_back(v);
        T[v].push_back(u);
    }

    
    return 0;
}