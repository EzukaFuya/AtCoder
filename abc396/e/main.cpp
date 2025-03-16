#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    Graph graph(N);

    for (int i = 0; i < M; i++) {
        int x, y;
        ll z;
        cin >> x >> y >> z;

        graph[x].push_back({y, z});
        graph[y].push_back({x, z});
    }
    return 0;
}