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

public:
    Solver(int n, int m, int k, int t, const vector<Person>& people)
        : n(n), m(m), k(k), t(t), people(people), field(n), money(k) {}

        void solve() {
            // 通勤距離でソート（収入の大きい順）
            vector<pair<int, int>> commute_distances;  // <distance, index>
            for (int i = 0; i < m; i++) {
                const auto& person = people[i];
                int distance = abs(person.home.r - person.work.r) + 
                              abs(person.home.c - person.work.c);
                commute_distances.emplace_back(distance, i);
            }
            sort(commute_distances.rbegin(), commute_distances.rend());  // 距離が大きい順
        
            // 上位2人を接続
            int connected = 0;
            for (const auto& [distance, idx] : commute_distances) {
                if (connected >= 2) break;  // 2人接続したら終了
                
                const auto& person = people[idx];
                
                // この人を接続するのに必要なコストを計算
                int rail_cost = (distance - 1) * COST_RAIL;  // 駅間の線路コスト
                int total_cost = COST_STATION * 2 + rail_cost;  // 駅2つ + 線路
                
                if (money >= total_cost) {
                    // 接続可能なら実行
                    buildStation(person.home);
                    buildStation(person.work);  // workplaceをworkに修正
                    connectStations(person.home, person.work);  // workplaceをworkに修正
                    connected++;
                    
                    // 収入を得る（建設余力を増やす）
                    money += calculateIncome();
                }
            }
            
            // 残りのターンは待機
            while (actions.size() < t) {
                doNothing();
                money += calculateIncome();
            }
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