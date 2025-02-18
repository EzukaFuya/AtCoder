#include <bits/stdc++.h>
using namespace std;

// 座標を表す構造体
struct Pos {
    int r, c;
    
    Pos(int row = 0, int col = 0) : r(row), c(col) {}
    
    int manhattan_distance(const Pos& other) const {
        return abs(r - other.r) + abs(c - other.c);
    }
    
    bool is_within_station_range(const Pos& other) const {
        return manhattan_distance(other) <= 2;
    }
    
    bool is_valid(int n) const {
        return r >= 0 && r < n && c >= 0 && c < n;
    }

    // 比較演算子を追加
    bool operator<(const Pos& other) const {
        if (r != other.r) return r < other.r;
        return c < other.c;
    }

    bool operator==(const Pos& other) const {
        return r == other.r && c == other.c;
    }
};

// 人（通勤者）を表す構造体
struct Person {
    Pos home;
    Pos workplace;
    
    Person(Pos h, Pos w) : home(h), workplace(w) {}
    
    int commute_distance() const {
        return home.manhattan_distance(workplace);
    }
};

// 通勤者の分析を行うクラス
class CommuterAnalyzer {
private:
    vector<Person> commuters;
    int grid_size;

public:
    CommuterAnalyzer(int n) : grid_size(n) {}

    // 入力を読み込む
    void read_input() {
        int n, m, k, t;
        cin >> n >> m >> k >> t;
        
        // m人分の通勤者データを読み込む
        for (int i = 0; i < m; i++) {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            commuters.emplace_back(Pos(r1, c1), Pos(r2, c2));
        }
        
        cout << "Read " << m << " commuters\n";
        cout << "Initial money: " << k << "\n";
        cout << "Turns: " << t << "\n";
    }

    // 通勤距離の分析
    void analyze_distances() {
        if (commuters.empty()) {
            cout << "No commuters to analyze\n";
            return;
        }

        // 最短、最長、平均通勤距離を計算
        int min_dist = INT_MAX;
        int max_dist = 0;
        long long total_dist = 0;

        for (const auto& person : commuters) {
            int dist = person.commute_distance();
            min_dist = min(min_dist, dist);
            max_dist = max(max_dist, dist);
            total_dist += dist;
        }

        double avg_dist = static_cast<double>(total_dist) / commuters.size();

        cout << "\nDistance Analysis:\n";
        cout << "Minimum distance: " << min_dist << "\n";
        cout << "Maximum distance: " << max_dist << "\n";
        cout << "Average distance: " << fixed << setprecision(2) << avg_dist << "\n";
    }

    // 混雑地域の分析（家と職場の分布）
    void analyze_density() {
        vector<vector<int>> home_density(grid_size, vector<int>(grid_size, 0));
        vector<vector<int>> work_density(grid_size, vector<int>(grid_size, 0));

        // 密度マップの作成
        for (const auto& person : commuters) {
            home_density[person.home.r][person.home.c]++;
            work_density[person.workplace.r][person.workplace.c]++;
        }

        // 最も混雑している地点を見つける
        int max_home = 0, max_work = 0;
        Pos max_home_pos, max_work_pos;

        for (int i = 0; i < grid_size; i++) {
            for (int j = 0; j < grid_size; j++) {
                if (home_density[i][j] > max_home) {
                    max_home = home_density[i][j];
                    max_home_pos = Pos(i, j);
                }
                if (work_density[i][j] > max_work) {
                    max_work = work_density[i][j];
                    max_work_pos = Pos(i, j);
                }
            }
        }

        cout << "\nDensity Analysis:\n";
        cout << "Most populated home area: (" << max_home_pos.r << "," 
             << max_home_pos.c << ") with " << max_home << " people\n";
        cout << "Most populated workplace: (" << max_work_pos.r << "," 
             << max_work_pos.c << ") with " << max_work << " people\n";
    }

    // 駅を建設すべき候補地点を提案
    void suggest_station_locations() {
        // 簡単な戦略：最も混雑している地点の周辺に駅を建設
        vector<vector<int>> density(grid_size, vector<int>(grid_size, 0));

        // 各地点の重要度を計算
        for (const auto& person : commuters) {
            // 家の周辺2マスの重要度を上げる
            for (int dr = -2; dr <= 2; dr++) {
                for (int dc = -2; dc <= 2; dc++) {
                    if (abs(dr) + abs(dc) > 2) continue;
                    
                    Pos p(person.home.r + dr, person.home.c + dc);
                    if (p.is_valid(grid_size)) {
                        density[p.r][p.c] += person.commute_distance();
                    }
                }
            }

            // 職場の周辺2マスの重要度を上げる
            for (int dr = -2; dr <= 2; dr++) {
                for (int dc = -2; dc <= 2; dc++) {
                    if (abs(dr) + abs(dc) > 2) continue;
                    
                    Pos p(person.workplace.r + dr, person.workplace.c + dc);
                    if (p.is_valid(grid_size)) {
                        density[p.r][p.c] += person.commute_distance();
                    }
                }
            }
        }

        // 上位5つの候補地点を表示
        vector<pair<int, Pos>> candidates;
        for (int i = 0; i < grid_size; i++) {
            for (int j = 0; j < grid_size; j++) {
                if (density[i][j] > 0) {
                    candidates.emplace_back(density[i][j], Pos(i, j));
                }
            }
        }

        sort(candidates.rbegin(), candidates.rend());

        cout << "\nTop 5 suggested station locations:\n";
        for (int i = 0; i < min(5, (int)candidates.size()); i++) {
            cout << i+1 << ". Position (" << candidates[i].second.r << "," 
                 << candidates[i].second.c << ") with importance score: " 
                 << candidates[i].first << "\n";
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // グリッドサイズは50固定
    CommuterAnalyzer analyzer(50);
    
    // 入力データを読み込む
    analyzer.read_input();
    
    // 分析を実行
    analyzer.analyze_distances();
    analyzer.analyze_density();
    analyzer.suggest_station_locations();

    return 0;
}