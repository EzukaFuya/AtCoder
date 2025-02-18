#include <bits/stdc++.h>
using namespace std;

// Constants
constexpr int EMPTY = -1;
constexpr int DO_NOTHING = -1;
constexpr int STATION = 0;
constexpr int RAIL_HORIZONTAL = 1;
constexpr int RAIL_VERTICAL = 2;
constexpr int RAIL_LEFT_DOWN = 3;
constexpr int RAIL_LEFT_UP = 4;
constexpr int RAIL_RIGHT_UP = 5;
constexpr int RAIL_RIGHT_DOWN = 6;
constexpr int COST_STATION = 5000;
constexpr int COST_RAIL = 100;

// Position structure
struct Pos {
    int r, c;
    Pos(int r = 0, int c = 0) : r(r), c(c) {}
    
    int manhattan_distance(const Pos& other) const {
        return abs(r - other.r) + abs(c - other.c);
    }
    
    bool is_within_range(const Pos& other) const {
        return manhattan_distance(other) <= 2;
    }
};

// Person structure
struct Person {
    Pos home, work;
    int distance;  // 通勤距離（=収入額）
    bool is_connected;  // 接続済みかどうか
    
    Person(Pos h, Pos w) : home(h), work(w), is_connected(false) {
        distance = h.manhattan_distance(w);
    }
    
    // 収入が大きい順でソート
    bool operator<(const Person& other) const {
        return distance > other.distance;
    }
};

// Station candidate structure
struct StationCandidate {
    Pos pos;
    int coverage;  // カバーできる人数
    int potential_income;  // 見込み収入
    
    StationCandidate(Pos p, int c, int i) : pos(p), coverage(c), potential_income(i) {}
    
    bool operator<(const StationCandidate& other) const {
        return potential_income > other.potential_income;
    }
};

// Union Find for connectivity
class UnionFind {
private:
    vector<int> parent;
    int n;

public:
    UnionFind(int size) : n(size) {
        parent.resize(size * size, -1);
    }

    int find(int x) {
        if (parent[x] < 0) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(const Pos& p1, const Pos& p2) {
        int x = p1.r * n + p1.c;
        int y = p2.r * n + p2.c;
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (parent[x] > parent[y]) swap(x, y);
        parent[x] += parent[y];
        parent[y] = x;
        return true;
    }

    bool same(const Pos& p1, const Pos& p2) {
        int x = p1.r * n + p1.c;
        int y = p2.r * n + p2.c;
        return find(x) == find(y);
    }
};

// Field class
class Field {
private:
    int n;
    vector<vector<int>> grid;
    UnionFind uf;

public:
    Field(int size) : n(size), grid(size, vector<int>(size, EMPTY)), uf(size) {}

    bool build(int type, const Pos& pos) {
        if (pos.r < 0 || pos.r >= n || pos.c < 0 || pos.c >= n) return false;
        if (grid[pos.r][pos.c] == STATION) return false;
        if (type >= 1 && type <= 6 && grid[pos.r][pos.c] != EMPTY) return false;
        
        grid[pos.r][pos.c] = type;
        connect_adjacent(pos, type);
        return true;
    }
    
    bool isConnected(const Pos& start, const Pos& end) {
        vector<Pos> stations1 = collectStations(start);
        vector<Pos> stations2 = collectStations(end);
        
        for (const auto& s1 : stations1) {
            for (const auto& s2 : stations2) {
                if (uf.same(s1, s2)) return true;
            }
        }
        return false;
    }
    
    vector<Pos> collectStations(const Pos& pos) {
        vector<Pos> stations;
        for (int dr = -2; dr <= 2; dr++) {
            for (int dc = -2; dc <= 2; dc++) {
                if (abs(dr) + abs(dc) > 2) continue;
                int r = pos.r + dr;
                int c = pos.c + dc;
                if (r >= 0 && r < n && c >= 0 && c < n && grid[r][c] == STATION) {
                    stations.emplace_back(r, c);
                }
            }
        }
        return stations;
    }

    bool cell_is_empty(const Pos& pos) const {
        return grid[pos.r][pos.c] == EMPTY;
    }

    vector<Pos> get_all_stations() const {
        vector<Pos> stations;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (grid[r][c] == STATION) {
                    stations.emplace_back(r, c);
                }
            }
        }
        return stations;
    }

private:
    void connect_adjacent(const Pos& pos, int type) {
        // Up
        if ((type == STATION || type == RAIL_VERTICAL || type == RAIL_LEFT_UP || type == RAIL_RIGHT_UP) &&
            pos.r > 0 && can_connect_up(grid[pos.r-1][pos.c])) {
            uf.unite(pos, Pos(pos.r-1, pos.c));
        }
        // Down
        if ((type == STATION || type == RAIL_VERTICAL || type == RAIL_LEFT_DOWN || type == RAIL_RIGHT_DOWN) &&
            pos.r < n-1 && can_connect_down(grid[pos.r+1][pos.c])) {
            uf.unite(pos, Pos(pos.r+1, pos.c));
        }
        // Left
        if ((type == STATION || type == RAIL_HORIZONTAL || type == RAIL_LEFT_DOWN || type == RAIL_LEFT_UP) &&
            pos.c > 0 && can_connect_left(grid[pos.r][pos.c-1])) {
            uf.unite(pos, Pos(pos.r, pos.c-1));
        }
        // Right
        if ((type == STATION || type == RAIL_HORIZONTAL || type == RAIL_RIGHT_DOWN || type == RAIL_RIGHT_UP) &&
            pos.c < n-1 && can_connect_right(grid[pos.r][pos.c+1])) {
            uf.unite(pos, Pos(pos.r, pos.c+1));
        }
    }

    static bool can_connect_up(int cell) {
        return cell == STATION || cell == RAIL_VERTICAL || 
               cell == RAIL_LEFT_DOWN || cell == RAIL_RIGHT_DOWN;
    }

    static bool can_connect_down(int cell) {
        return cell == STATION || cell == RAIL_VERTICAL || 
               cell == RAIL_LEFT_UP || cell == RAIL_RIGHT_UP;
    }

    static bool can_connect_left(int cell) {
        return cell == STATION || cell == RAIL_HORIZONTAL || 
               cell == RAIL_RIGHT_DOWN || cell == RAIL_RIGHT_UP;
    }

    static bool can_connect_right(int cell) {
        return cell == STATION || cell == RAIL_HORIZONTAL || 
               cell == RAIL_LEFT_DOWN || cell == RAIL_LEFT_UP;
    }
};

// Solver class
class Solver {
private:
    int n, m, k, t;
    vector<Person> people;
    Field field;
    long long money;
    vector<pair<int, Pos>> actions;

    long long calculateIncome() {
        long long income = 0;
        for (auto& person : people) {
            if (field.isConnected(person.home, person.work)) {
                income += person.distance;
                person.is_connected = true;
            }
        }
        return income;
    }
    
    bool buildRail(int type, const Pos& pos) {
        if (money < COST_RAIL) return false;
        if (!field.build(type, pos)) return false;
        money -= COST_RAIL;
        actions.emplace_back(type, pos);
        return true;
    }
    
    bool buildStation(const Pos& pos) {
        if (money < COST_STATION) return false;
        if (!field.build(STATION, pos)) return false;
        money -= COST_STATION;
        actions.emplace_back(STATION, pos);
        return true;
    }
    
    void doNothing() {
        actions.emplace_back(DO_NOTHING, Pos());
    }

    vector<StationCandidate> evaluate_station_positions() {
        vector<StationCandidate> candidates;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                Pos pos(r, c);
                if (!field.cell_is_empty(pos)) continue;

                int coverage = 0;
                int income = 0;
                for (const auto& person : people) {
                    if (person.is_connected) continue;
                    if (pos.is_within_range(person.home) ||
                        pos.is_within_range(person.work)) {
                        coverage++;
                        income += person.distance;
                    }
                }
                if (coverage > 0) {
                    candidates.emplace_back(pos, coverage, income);
                }
            }
        }
        sort(candidates.begin(), candidates.end());
        return candidates;
    }

    void connect_nearby_stations() {
        auto stations = field.get_all_stations();
        for (size_t i = 0; i < stations.size(); i++) {
            for (size_t j = i + 1; j < stations.size(); j++) {
                if (!field.isConnected(stations[i], stations[j])) {
                    int rail_cost = (stations[i].manhattan_distance(stations[j]) - 1) * COST_RAIL;
                    if (money >= rail_cost) {
                        connectStations(stations[i], stations[j]);
                    }
                }
            }
        }
    }

    void connectStations(const Pos& start, const Pos& end) {
        int r0 = start.r, c0 = start.c;
        int r1 = end.r, c1 = end.c;
        
        if (r0 < r1) {
            for (int r = r0 + 1; r < r1; r++) {
                buildRail(RAIL_VERTICAL, Pos(r, c0));
            }
            if (c0 < c1) {
                buildRail(RAIL_RIGHT_UP, Pos(r1, c0));
            } else if (c0 > c1) {
                buildRail(RAIL_LEFT_UP, Pos(r1, c0));
            }
        } else if (r0 > r1) {
            for (int r = r0 - 1; r > r1; r--) {
                buildRail(RAIL_VERTICAL, Pos(r, c0));
            }
            if (c0 < c1) {
                buildRail(RAIL_RIGHT_DOWN, Pos(r1, c0));
            } else if (c0 > c1) {
                buildRail(RAIL_LEFT_DOWN, Pos(r1, c0));
            }
        }
        
        if (c0 < c1) {
            for (int c = c0 + 1; c < c1; c++) {
                buildRail(RAIL_HORIZONTAL, Pos(r1, c));
            }
        } else if (c0 > c1) {
            for (int c = c0 - 1; c > c1; c--) {
                buildRail(RAIL_HORIZONTAL, Pos(r1, c));
            }
        }
    }

public:
    Solver(int n, int m, int k, int t) 
        : n(n), m(m), k(k), t(t), field(n), money(k) {}
    
    void add_person(const Pos& home, const Pos& work) {
        people.emplace_back(home, work);
    }
    
    void solve() {
        // 通勤距離が長い順にソート
        sort(people.begin(), people.end());
        
        // 建設フェーズ: 資金の80%を使用
        while (money >= COST_STATION && actions.size() < t * 0.6) {
            // 駅の候補地を評価
            auto candidates = evaluate_station_positions();
            if (candidates.empty()) break;
            
            // 最も効果的な位置に駅を建設
            const auto& best = candidates[0];
            if (best.potential_income * (t - actions.size()) < COST_STATION) break;
            
            buildStation(best.pos);
            // 既存の駅と接続を試みる
            connect_nearby_stations();
            
            // 収入を得る
            money += calculateIncome();
        }
        
        // 残りのターンは収入を得る
        while (actions.size() < t) {
            doNothing();
            money += calculateIncome();
        }
    }
    
    void output() const {
        for (const auto& action : actions) {
            if (action.first == DO_NOTHING) {
                cout << -1 << "\n";
            } else {
                cout << action.first << " " << action.second.r << " " 
                     << action.second.c << "\n";
            }
        }
        cerr << "Final money: " << money << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k, t;
    cin >> n >> m >> k >> t;
    
    Solver solver(n, m, k, t);
    
    for (int i = 0; i < m; i++) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        solver.add_person(Pos(r1, c1), Pos(r2, c2));
    }
    
    solver.solve();
    solver.output();
    
    return 0;
}