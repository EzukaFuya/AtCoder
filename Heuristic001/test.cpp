#include <bits/stdc++.h>
#include <filesystem>
#include <fstream>
using namespace std;

#define TEST

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

    // マンハッタン距離を計算
    int manhattan_distance(const Pos& other) const {
        return abs(r - other.r) + abs(c - other.c);
    }

    // グリッド内の有効な座標かチェック
    bool is_valid(int n) const {
        return r >= 0 && r < n && c >= 0 && c < n;
    }

    // 演算子のオーバーロード（map用）
    bool operator<(const Pos& other) const {
        if (r != other.r) return r < other.r;
        return c < other.c;
    }

    // 等価比較演算子を追加
    bool operator==(const Pos& other) const {
        return r == other.r && c == other.c;
    }

    // 新しいC++で推奨される不等価演算子も追加
    bool operator!=(const Pos& other) const {
        return !(*this == other);
    }
};

// Person structure
struct Person {
    Pos home, work;
    Person(Pos h, Pos w) : home(h), work(w) {}
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

// Field class to manage the railway network
class Field {
private:
    int n;
    vector<vector<int>> grid;
    UnionFind uf;

public:
    Field(int size) : n(size), grid(size, vector<int>(size, EMPTY)), uf(size) {}

    // 追加するメソッド
    int get_cell(const Pos& pos) const {
        return grid[pos.r][pos.c];
    }

    bool build(int type, const Pos& pos) {
        int r = pos.r, c = pos.c;
        if (r < 0 || r >= n || c < 0 || c >= n) return false;
        if (grid[r][c] == STATION) return false;
        if (type >= 1 && type <= 6 && grid[r][c] != EMPTY) return false;
        
        grid[r][c] = type;
        
        // Connect to adjacent cells
        // Up
        if (type == STATION || type == RAIL_VERTICAL || type == RAIL_LEFT_UP || type == RAIL_RIGHT_UP) {
            if (r > 0 && (grid[r-1][c] == STATION || grid[r-1][c] == RAIL_VERTICAL || 
                grid[r-1][c] == RAIL_LEFT_DOWN || grid[r-1][c] == RAIL_RIGHT_DOWN)) {
                uf.unite(Pos(r, c), Pos(r-1, c));
            }
        }
        // Down
        if (type == STATION || type == RAIL_VERTICAL || type == RAIL_LEFT_DOWN || type == RAIL_RIGHT_DOWN) {
            if (r < n-1 && (grid[r+1][c] == STATION || grid[r+1][c] == RAIL_VERTICAL || 
                grid[r+1][c] == RAIL_LEFT_UP || grid[r+1][c] == RAIL_RIGHT_UP)) {
                uf.unite(Pos(r, c), Pos(r+1, c));
            }
        }
        // Left
        if (type == STATION || type == RAIL_HORIZONTAL || type == RAIL_LEFT_DOWN || type == RAIL_LEFT_UP) {
            if (c > 0 && (grid[r][c-1] == STATION || grid[r][c-1] == RAIL_HORIZONTAL || 
                grid[r][c-1] == RAIL_RIGHT_DOWN || grid[r][c-1] == RAIL_RIGHT_UP)) {
                uf.unite(Pos(r, c), Pos(r, c-1));
            }
        }
        // Right
        if (type == STATION || type == RAIL_HORIZONTAL || type == RAIL_RIGHT_DOWN || type == RAIL_RIGHT_UP) {
            if (c < n-1 && (grid[r][c+1] == STATION || grid[r][c+1] == RAIL_HORIZONTAL || 
                grid[r][c+1] == RAIL_LEFT_DOWN || grid[r][c+1] == RAIL_LEFT_UP)) {
                uf.unite(Pos(r, c), Pos(r, c+1));
            }
        }
        
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
};

// Solver class
class Solver {
    private:
        // 補助構造体の定義を先頭に移動
        struct SharingInfo {
            bool can_share;
            Pos station;
            SharingInfo() : can_share(false) {}
        };
        
        struct RouteInfo {
            int idx;
            int distance;
            int total_cost;
            SharingInfo home_sharing;
            SharingInfo work_sharing;
            double roi;
        
            bool operator<(const RouteInfo& other) const {
                return roi > other.roi;
            }
        };
    
        // メンバ変数
        int n, m, k, t;
        vector<Person> people;
        Field field;
        long long money;
        vector<pair<int, Pos>> actions;

        long long calculateIncome() {
            long long income = 0;
            for (const auto& person : people) {
                if (field.isConnected(person.home, person.work)) {
                    income += abs(person.home.r - person.work.r) + 
                            abs(person.home.c - person.work.c);
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

    private:
        // 駅の共有可能性を評価
        SharingInfo evaluateStationSharing(const Pos& pos) {
            SharingInfo info;
            vector<Pos> stations = collectCurrentStations();
            
            for (const auto& station : stations) {
                if (abs(station.r - pos.r) + abs(station.c - pos.c) <= 2) {
                    info.can_share = true;
                    info.station = station;
                    break;
                }
            }
            return info;
        }

    public:
        Solver(int n, int m, int k, int t, const vector<Person>& people)
            : n(n), m(m), k(k), t(t), people(people), field(n), money(k) {}

        void solve() {
            // 通勤者情報の分析
            vector<pair<int, int>> commute_distances;
            map<pair<int,int>, vector<int>> position_people;
        
            for (int i = 0; i < m; i++) {
                const auto& person = people[i];
                int distance = abs(person.home.r - person.work.r) + 
                              abs(person.home.c - person.work.c);
                commute_distances.emplace_back(distance, i);
                position_people[{person.home.r, person.home.c}].push_back(i);
                position_people[{person.work.r, person.work.c}].push_back(i);
            }
            sort(commute_distances.rbegin(), commute_distances.rend());
        
            // 最長路線の建設
            const auto& [max_distance, max_idx] = commute_distances[0];
            if (money >= COST_STATION * 2 + (max_distance - 1) * COST_RAIL) {
                const auto& person = people[max_idx];
                buildStation(person.home);
                buildStation(person.work);
                connectStations(person.home, person.work);
                money += calculateIncome();
        
                // 他の路線のための待機
                for (int i = 0; i < 5 && actions.size() < t; i++) {
                    doNothing();
                    money += calculateIncome();
                }
            }
        
            // 残りの路線を評価
            vector<RouteInfo> routes;
            for (size_t i = 1; i < commute_distances.size(); i++) {
                const auto& [distance, idx] = commute_distances[i];
                if (distance < 10) continue;  // 短すぎる路線は除外
        
                const auto& person = people[idx];
                
                // 両端での駅共有可能性を評価
                auto home_sharing = evaluateStationSharing(person.home);
                auto work_sharing = evaluateStationSharing(person.work);
        
                int total_cost = COST_STATION * 2 - 
                                (home_sharing.can_share ? COST_STATION : 0) - 
                                (work_sharing.can_share ? COST_STATION : 0) +
                                (distance - 1) * COST_RAIL;
        
                if (home_sharing.can_share && work_sharing.can_share && 
                    home_sharing.station == work_sharing.station) continue;  // 同じ駅を共有する場合は除外
        
                routes.push_back({
                    idx,
                    distance,
                    total_cost,
                    home_sharing,
                    work_sharing,
                    distance * 800.0 / total_cost  // ROI
                });
            }
        
            // ROIでソート
            sort(routes.begin(), routes.end());
        
            // 効率の良い路線から建設
            for (const auto& route : routes) {
                if (actions.size() >= t * 0.6) break;
                if (money < route.total_cost) continue;
        
                const auto& person = people[route.idx];
                bool success = true;
        
                // 必要な駅のみを建設
                if (!route.home_sharing.can_share) {
                    if (!buildStation(person.home)) success = false;
                }
                if (!route.work_sharing.can_share && success) {
                    if (!buildStation(person.work)) success = false;
                }
        
                if (success) {
                    // 適切な端点を選んで接続
                    Pos start = route.home_sharing.can_share ? 
                               route.home_sharing.station : person.home;
                    Pos end = route.work_sharing.can_share ? 
                             route.work_sharing.station : person.work;
                    connectStations(start, end);
                    
                    money += calculateIncome();
        
                    // 次の建設のための待機
                    int wait_turns = min(5, route.total_cost / route.distance);
                    for (int i = 0; i < wait_turns && actions.size() < t; i++) {
                        doNothing();
                        money += calculateIncome();
                    }
                }
            }
        
            // 残りのターンは待機
            while (actions.size() < t) {
                doNothing();
                money += calculateIncome();
            }
        }

        // 現在の駅の位置を取得
        vector<Pos> collectCurrentStations() {
            vector<Pos> stations;
            for (int r = 0; r < n; r++) {
                for (int c = 0; c < n; c++) {
                    if (field.get_cell(Pos(r, c)) == STATION) {
                        stations.emplace_back(r, c);
                    }
                }
            }
            return stations;
        }
        
        // 指定位置の近くに駅があるかチェック
        bool hasNearbyStation(const Pos& pos) {
            for (int dr = -2; dr <= 2; dr++) {
                for (int dc = -2; dc <= 2; dc++) {
                    if (abs(dr) + abs(dc) > 2) continue;
                    Pos check(pos.r + dr, pos.c + dc);
                    if (check.is_valid(n) && field.get_cell(check) == STATION) {
                        return true;
                    }
                }
            }
            return false;
        }
    
    void outputResult() {
        for (const auto& action : actions) {
            cout << action.first << " ";
            if (action.first != DO_NOTHING) {
                cout << action.second.r << " " << action.second.c;
            }
            cout << "\n";
        }
    }
    
private:
    void connectStations(const Pos& start, const Pos& end) {
        int r0 = start.r, c0 = start.c;
        int r1 = end.r, c1 = end.c;
        
        // Build rails from start to end
        if (r0 < r1) {
            // Going down
            for (int r = r0 + 1; r < r1; r++) {
                buildRail(RAIL_VERTICAL, Pos(r, c0));
            }
            if (c0 < c1) {
                buildRail(RAIL_RIGHT_UP, Pos(r1, c0));
            } else if (c0 > c1) {
                buildRail(RAIL_LEFT_UP, Pos(r1, c0));
            }
        } else if (r0 > r1) {
            // Going up
            for (int r = r0 - 1; r > r1; r--) {
                buildRail(RAIL_VERTICAL, Pos(r, c0));
            }
            if (c0 < c1) {
                buildRail(RAIL_RIGHT_DOWN, Pos(r1, c0));
            } else if (c0 > c1) {
                buildRail(RAIL_LEFT_DOWN, Pos(r1, c0));
            }
        }
        
        // Build horizontal rails
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
    long long getFinalMoney() const {
        return money;
    }
};

#ifdef TEST
int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string test_dir = "test";
    string out_dir = "out";
    filesystem::create_directory(out_dir);

    // スコア統計用の変数
    vector<pair<string, long long>> scores;
    long long total_score = 0;
    long long min_score = LLONG_MAX;
    long long max_score = LLONG_MIN;
    
    for (const auto& entry : filesystem::directory_iterator(test_dir)) {
        string input_path = entry.path().string();
        string filename = entry.path().filename().string();
        string output_path = out_dir + "/" + filename.substr(0, filename.find_last_of('.')) + "_out.txt";
        
        ifstream in(input_path);
        if (!in) {
            cerr << "Failed to open input file: " << input_path << endl;
            continue;
        }
        
        ofstream out(output_path);
        if (!out) {
            cerr << "Failed to open output file: " << output_path << endl;
            continue;
        }
        
        int n, m, k, t;
        in >> n >> m >> k >> t;
        
        vector<Person> people;
        for (int i = 0; i < m; i++) {
            int r1, c1, r2, c2;
            in >> r1 >> c1 >> r2 >> c2;
            people.emplace_back(Pos(r1, c1), Pos(r2, c2));
        }
        
        Solver solver(n, m, k, t, people);
        solver.solve();
        
        auto cout_buf = cout.rdbuf();
        cout.rdbuf(out.rdbuf());
        solver.outputResult();
        cout.rdbuf(cout_buf);

        // スコアを記録
        long long score = solver.getFinalMoney();
        scores.emplace_back(filename, score);
        total_score += score;
        min_score = min(min_score, score);
        max_score = max(max_score, score);
        
        cerr << "Processed " << filename << ": Score = " << score << endl;
    }
    
    // 統計情報をファイルに出力
    ofstream stats(out_dir + "/statistics.txt");
    stats << "=== Score Statistics ===" << endl;
    stats << "Total test cases: " << scores.size() << endl;
    stats << "Average score: " << (scores.empty() ? 0 : total_score / scores.size()) << endl;
    stats << "Minimum score: " << (scores.empty() ? 0 : min_score) << endl;
    stats << "Maximum score: " << (scores.empty() ? 0 : max_score) << endl;
    stats << "\nDetailed scores:" << endl;
    
    for (const auto& [filename, score] : scores) {
        stats << filename << ": " << score << endl;
    }
    
    // 標準エラー出力にも表示
    cerr << "\n=== Score Statistics ===" << endl;
    cerr << "Total test cases: " << scores.size() << endl;
    cerr << "Average score: " << (scores.empty() ? 0 : total_score / scores.size()) << endl;
    cerr << "Minimum score: " << (scores.empty() ? 0 : min_score) << endl;
    cerr << "Maximum score: " << (scores.empty() ? 0 : max_score) << endl;
    
    return 0;
}

#else
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k, t;
    cin >> n >> m >> k >> t;
    
    vector<Person> people;
    for (int i = 0; i < m; i++) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        people.emplace_back(Pos(r1, c1), Pos(r2, c2));
    }
    
    Solver solver(n, m, k, t, people);
    
    solver.solve();
    solver.outputResult();
    
    return 0;
}
#endif