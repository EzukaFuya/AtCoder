#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    static const int MAX_SIZE = (2 << 17);
    int parent_size[MAX_SIZE];  // 元のunicntと同じ
    vector<vector<array<int,3>>> extra_edges;  // 元のamariと同じ

public:
    UnionFind(int n) : extra_edges(n) {
        for (int i = 0; i < n; i++) {
            parent_size[i] = 1;
        }
    }

    int root(int x) {
        if (parent_size[x] <= 0) {
            return -(parent_size[x] = -root(-parent_size[x]));
        }
        return x;
    }

    bool is_same(int x, int y) {
        return root(x) == root(y);
    }

    void unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) return;

        if (parent_size[x] < parent_size[y]) swap(x, y);
        parent_size[x] += parent_size[y];
        parent_size[y] = -x;

        // 余分な辺の移動
        extra_edges[x].insert(extra_edges[x].end(),
                            extra_edges[y].begin(),
                            extra_edges[y].end());
        extra_edges[y].clear();
    }

    void add_extra_edge(int x, int y, int i) {
        extra_edges[root(x)].push_back({x, y, i});
    }

    vector<pair<int,int>> get_components() {
        vector<pair<int,int>> comps;
        for (int i = 0; i < extra_edges.size(); i++) {
            if (root(i) == i) {
                comps.push_back({extra_edges[i].size(), i});
            }
        }
        return comps;
    }

    const vector<array<int,3>>& get_extra_edges(int root_id) {
        return extra_edges[root_id];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    UnionFind uf(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        
        if (uf.is_same(x, y)) {
            uf.add_extra_edge(x, y, i);
        } else {
            uf.unite(x, y);
        }
    }

    auto components = uf.get_components();
    sort(components.rbegin(), components.rend());

    cout << components.size() - 1 << endl;

    int pos = 1;
    for (const auto& [_, root] : components) {
        for (const auto& [x, y, i] : uf.get_extra_edges(root)) {
            if (pos < components.size()) {
                cout << i + 1 << ' ' << x + 1 << ' ' 
                     << components[pos++].second + 1 << endl;
            }
        }
    }

    return 0;
}