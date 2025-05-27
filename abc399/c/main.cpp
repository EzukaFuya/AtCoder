#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

class DisjointSet {
    private:
        vector<int> parent, rank;
    public:
        DisjointSet(int n) {
            parent.resize(n+1);
            rank.resize(n+1, 0);
            for (int i = 0; i <= n; i++) {
                parent[i] = i;
            }
        }

        int find(int x) {
            if (parent[x] == x) {
                return x;
            }
            return parent[x] = find(parent[x]);
        }
        void unite(int x, int y) {
            x = find(x);
            y = find(y);

            if (x == y) return;

            if (rank[x] < rank[y]) {
                parent[x] = y;
            } else {
                parent[y] = x;
                if (rank[x] == rank[y]) rank[x]++;
            }
        }

        bool same(int x, int y) {
            return find(x) == find(y);
        }
};

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    DisjointSet ds(N);
    int cycleCount = 0;

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;

        if (ds.find(u) == ds.find(v)) {
            cycleCount++;
        } else {
            ds.unite(u, v);
        }
    }

    cout << cycleCount << endl;

    return 0;
}