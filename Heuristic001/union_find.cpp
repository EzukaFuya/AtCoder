#include <bits/stdc++.h>
using namespace std;

// Positionの定義（前回と同じ）
struct Pos {
    int r, c;
    
    Pos(int row = 0, int col = 0) : r(row), c(c) {}
    
    int manhattan_distance(const Pos& other) const {
        return abs(r - other.r) + abs(c - other.c);
    }
    
    bool is_within_station_range(const Pos& other) const {
        return manhattan_distance(other) <= 2;
    }
    
    bool is_valid(int n) const {
        return r >= 0 && r < n && c >= 0 && c < n;
    }

    bool operator<(const Pos& other) const {
        if (r != other.r) return r < other.r;
        return c < other.c;
    }

    bool operator==(const Pos& other) const {
        return r == other.r && c == other.c;
    }
};

// UnionFindクラス：接続された駅や線路のグループを管理
class UnionFind {
private:
    vector<int> parent;  // 親要素を保持
    vector<int> size;    // グループのサイズを保持
    int grid_size;       // グリッドのサイズ

    // 2次元座標を1次元インデックスに変換
    int pos_to_index(const Pos& p) const {
        return p.r * grid_size + p.c;
    }

public:
    UnionFind(int n) : grid_size(n) {
        int total_cells = n * n;
        parent.resize(total_cells);
        size.resize(total_cells, 1);
        
        // 初期化：各要素の親は自分自身
        for (int i = 0; i < total_cells; i++) {
            parent[i] = i;
        }
    }

    // 要素の根を見つける（経路圧縮あり）
    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);  // 経路圧縮
    }

    // 位置pの根を見つける
    int find(const Pos& p) {
        return find(pos_to_index(p));
    }

    // 2つの要素を結合
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        
        if (x == y) return;  // すでに同じグループ
        
        // サイズの大きい方に小さい方をくっつける
        if (size[x] < size[y]) {
            swap(x, y);
        }
        parent[y] = x;
        size[x] += size[y];
    }

    // 2つの位置を結合
    void unite(const Pos& p1, const Pos& p2) {
        unite(pos_to_index(p1), pos_to_index(p2));
    }

    // 2つの要素が同じグループに属しているか判定
    bool same(int x, int y) {
        return find(x) == find(y);
    }

    // 2つの位置が接続されているか判定
    bool same(const Pos& p1, const Pos& p2) {
        return same(pos_to_index(p1), pos_to_index(p2));
    }

    // グループのサイズを取得
    int get_size(int x) {
        return size[find(x)];
    }

    // 位置のグループサイズを取得
    int get_size(const Pos& p) {
        return get_size(pos_to_index(p));
    }
};

// テスト用のメイン関数
int main() {
    // グリッドサイズ
    int n = 5;
    UnionFind uf(n);

    // テストケース
    cout << "Testing UnionFind with 5x5 grid:\n\n";

    // 接続テスト
    Pos p1(1, 1);
    Pos p2(1, 2);
    Pos p3(2, 2);

    cout << "Initially connected? " << (uf.same(p1, p2) ? "Yes" : "No") << "\n";
    
    // p1とp2を接続
    uf.unite(p1, p2);
    cout << "After connecting (1,1) and (1,2): " << (uf.same(p1, p2) ? "Yes" : "No") << "\n";
    
    // p2とp3を接続
    uf.unite(p2, p3);
    cout << "After connecting (1,2) and (2,2):\n";
    cout << "(1,1) and (2,2) connected? " << (uf.same(p1, p3) ? "Yes" : "No") << "\n";
    
    // グループサイズの確認
    cout << "Group size for (1,1): " << uf.get_size(p1) << "\n";

    return 0;
}