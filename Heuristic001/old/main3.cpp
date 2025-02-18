#include <bits/stdc++.h>
using namespace std;

// 定数定義
const int EMPTY = -1;
const int STATION = 0;
const int RAIL_HORIZONTAL = 1;
const int RAIL_VERTICAL = 2;
const int RAIL_LEFT_DOWN = 3;
const int RAIL_LEFT_UP = 4;
const int RAIL_RIGHT_UP = 5;
const int RAIL_RIGHT_DOWN = 6;

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
    mutable vector<int> parent;  // mutableを追加
    vector<int> size;
    int grid_size;

    int pos_to_index(const Pos& p) const {
        return p.r * grid_size + p.c;
    }

public:
    UnionFind(int n) : grid_size(n) {
        int total_cells = n * n;
        parent.resize(total_cells);
        size.resize(total_cells, 1);
        
        for (int i = 0; i < total_cells; i++) {
            parent[i] = i;
        }
    }

    int find(int x) const {  // constを追加
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);  // mutableなので変更可能
    }

    int find(const Pos& p) const {  // constを追加
        return find(pos_to_index(p));
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        
        if (x == y) return;
        
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
    }

    void unite(const Pos& p1, const Pos& p2) {
        unite(pos_to_index(p1), pos_to_index(p2));
    }

    bool same(int x, int y) const {  // constを追加
        return find(x) == find(y);
    }

    bool same(const Pos& p1, const Pos& p2) const {  // constを追加
        return same(pos_to_index(p1), pos_to_index(p2));
    }

    int get_size(int x) const {  // constを追加
        return size[find(x)];
    }

    int get_size(const Pos& p) const {  // constを追加
        return get_size(pos_to_index(p));
    }
};

// Fieldクラス：グリッドの状態を管理
class Field {
private:
    int n;                          // グリッドサイズ
    vector<vector<int>> grid;       // グリッドの状態
    UnionFind uf;                   // 接続関係の管理
    
    // 指定された位置が有効な接続先かチェック
    bool is_valid_connection(const Pos& pos, int type, int direction) const {
        if (!pos.is_valid(n)) return false;
        
        int cell = grid[pos.r][pos.c];
        if (cell == EMPTY) return false;
        
        // direction: 0=上, 1=右, 2=下, 3=左
        switch (direction) {
            case 0: // 上への接続
                return cell == STATION || cell == RAIL_VERTICAL || 
                       cell == RAIL_LEFT_DOWN || cell == RAIL_RIGHT_DOWN;
            case 1: // 右への接続
                return cell == STATION || cell == RAIL_HORIZONTAL || 
                       cell == RAIL_LEFT_DOWN || cell == RAIL_LEFT_UP;
            case 2: // 下への接続
                return cell == STATION || cell == RAIL_VERTICAL || 
                       cell == RAIL_LEFT_UP || cell == RAIL_RIGHT_UP;
            case 3: // 左への接続
                return cell == STATION || cell == RAIL_HORIZONTAL || 
                       cell == RAIL_RIGHT_DOWN || cell == RAIL_RIGHT_UP;
        }
        return false;
    }

public:
    Field(int size) : n(size), grid(size, vector<int>(size, EMPTY)), uf(size) {}
    
    // グリッドの状態を取得
    int get_cell(const Pos& pos) const {
        return grid[pos.r][pos.c];
    }
    
    // 建設可能かチェック
    bool can_build(const Pos& pos, int type) const {
        if (!pos.is_valid(n)) return false;
        if (grid[pos.r][pos.c] == STATION) return false;
        if (type >= 1 && type <= 6 && grid[pos.r][pos.c] != EMPTY) return false;
        return true;
    }
    
    // 駅または線路を建設
    bool build(const Pos& pos, int type) {
        if (!can_build(pos, type)) return false;
        
        grid[pos.r][pos.c] = type;
        
        // 隣接するセルとの接続をチェック
        // 上
        if ((type == STATION || type == RAIL_VERTICAL || 
             type == RAIL_LEFT_UP || type == RAIL_RIGHT_UP) && 
            pos.r > 0 && is_valid_connection(Pos(pos.r-1, pos.c), type, 2)) {
            uf.unite(pos, Pos(pos.r-1, pos.c));
        }
        
        // 右
        if ((type == STATION || type == RAIL_HORIZONTAL || 
             type == RAIL_RIGHT_DOWN || type == RAIL_RIGHT_UP) && 
            pos.c < n-1 && is_valid_connection(Pos(pos.r, pos.c+1), type, 3)) {
            uf.unite(pos, Pos(pos.r, pos.c+1));
        }
        
        // 下
        if ((type == STATION || type == RAIL_VERTICAL || 
             type == RAIL_LEFT_DOWN || type == RAIL_RIGHT_DOWN) && 
            pos.r < n-1 && is_valid_connection(Pos(pos.r+1, pos.c), type, 0)) {
            uf.unite(pos, Pos(pos.r+1, pos.c));
        }
        
        // 左
        if ((type == STATION || type == RAIL_HORIZONTAL || 
             type == RAIL_LEFT_DOWN || type == RAIL_LEFT_UP) && 
            pos.c > 0 && is_valid_connection(Pos(pos.r, pos.c-1), type, 1)) {
            uf.unite(pos, Pos(pos.r, pos.c-1));
        }
        
        return true;
    }
    
    // 二点間の接続を確認
    bool is_connected(const Pos& p1, const Pos& p2) const {
        vector<Pos> stations1 = collect_stations(p1);
        vector<Pos> stations2 = collect_stations(p2);
        
        for (const auto& s1 : stations1) {
            for (const auto& s2 : stations2) {
                if (uf.same(s1, s2)) return true;
            }
        }
        return false;
    }
    
    // 指定位置の周囲2マス以内の駅を収集
    vector<Pos> collect_stations(const Pos& pos) const {
        vector<Pos> stations;
        for (int dr = -2; dr <= 2; dr++) {
            for (int dc = -2; dc <= 2; dc++) {
                if (abs(dr) + abs(dc) > 2) continue;
                
                Pos p(pos.r + dr, pos.c + dc);
                if (p.is_valid(n) && grid[p.r][p.c] == STATION) {
                    stations.push_back(p);
                }
            }
        }
        return stations;
    }
    
    // デバッグ用：現在の状態を出力
    void print_state() const {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == EMPTY) cout << ".";
                else if (grid[i][j] == STATION) cout << "S";
                else cout << grid[i][j];
            }
            cout << "\n";
        }
    }
};

// 行動を表す構造体
struct Action {
    int type;  // -1:待機, 0:駅建設, 1-6:線路建設
    Pos pos;
    
    Action(int t = -1, Pos p = Pos()) : type(t), pos(p) {}
    
    void output() const {
        if (type == -1) {
            cout << -1 << "\n";
        } else {
            cout << type << " " << pos.r << " " << pos.c << "\n";
        }
    }
};

// 通勤者を表す構造体
struct Person {
    Pos home, workplace;
    int distance;  // 通勤距離（収入額）
    
    Person(Pos h, Pos w) : home(h), workplace(w) {
        distance = h.manhattan_distance(w);
    }
    
    // 収入が大きい順でソート
    bool operator<(const Person& other) const {
        return distance > other.distance;
    }
};

// 駅の候補地点を表す構造体
struct StationCandidate {
    Pos pos;
    double score;                    // 基本スコア
    double spacing_score;            // 他の駅との距離に基づくスコア
    double coverage_score;           // カバーする人数に基づくスコア
    vector<int> covered_people;      // カバーできる人のインデックス
    set<int> unique_covered_people;  // 他の駅でカバーされていない人
    
    StationCandidate(Pos p) : pos(p), score(0), spacing_score(0), coverage_score(0) {}
    
    // 総合スコアの計算
    double total_score() const {
        return score * 0.4 + spacing_score * 0.3 + coverage_score * 0.3;
    }
    
    bool operator<(const StationCandidate& other) const {
        return total_score() > other.total_score();
    }
};

class Solver {
private:
    int n, m, k, t;  // グリッドサイズ、人数、初期資金、ターン数
    vector<Person> people;  // 通勤者のリスト
    Field field;  // フィールドの状態
    vector<Action> actions;  // 行動履歴
    long long money;  // 現在の資金
    
    // 収入を計算
    long long calculate_income() const {
        long long income = 0;
        for (const auto& person : people) {
            if (field.is_connected(person.home, person.workplace)) {
                income += person.distance;
            }
        }
        return income;
    }
    
    // 駅を建設
    bool build_station(const Pos& pos) {
        if (money < 5000) return false;  // 資金不足
        if (!field.build(pos, STATION)) return false;  // 建設失敗
        
        money -= 5000;
        actions.emplace_back(STATION, pos);
        return true;
    }
    
    // 線路を建設
    bool build_rail(const Pos& pos, int type) {
        if (money < 100) return false;  // 資金不足
        if (!field.build(pos, type)) return false;  // 建設失敗
        
        money -= 100;
        actions.emplace_back(type, pos);
        return true;
    }
    
    // 二点間を線路で接続
    void connect_stations(const Pos& start, const Pos& end) {
        int r0 = start.r, c0 = start.c;
        int r1 = end.r, c1 = end.c;
        
        // まず縦方向に移動
        if (r0 < r1) {
            // 下方向
            for (int r = r0 + 1; r < r1; r++) {
                build_rail(Pos(r, c0), RAIL_VERTICAL);
            }
            if (c0 < c1) {
                build_rail(Pos(r1, c0), RAIL_RIGHT_UP);
            } else if (c0 > c1) {
                build_rail(Pos(r1, c0), RAIL_LEFT_UP);
            }
        } else if (r0 > r1) {
            // 上方向
            for (int r = r0 - 1; r > r1; r--) {
                build_rail(Pos(r, c0), RAIL_VERTICAL);
            }
            if (c0 < c1) {
                build_rail(Pos(r1, c0), RAIL_RIGHT_DOWN);
            } else if (c0 > c1) {
                build_rail(Pos(r1, c0), RAIL_LEFT_DOWN);
            }
        }
        
        // 次に横方向に移動
        if (c0 < c1) {
            for (int c = c0 + 1; c < c1; c++) {
                build_rail(Pos(r1, c), RAIL_HORIZONTAL);
            }
        } else if (c0 > c1) {
            for (int c = c0 - 1; c > c1; c--) {
                build_rail(Pos(r1, c), RAIL_HORIZONTAL);
            }
        }
    }

    // 近くの駅同士を接続
    void connect_nearby_stations() {
        vector<Pos> stations;
        // 現在の駅の位置を収集
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (field.get_cell(Pos(r, c)) == STATION) {
                    stations.emplace_back(r, c);
                }
            }
        }
        
        // 各駅ペアについて
        for (int i = 0; i < stations.size(); i++) {
            for (int j = i + 1; j < stations.size(); j++) {
                const auto& s1 = stations[i];
                const auto& s2 = stations[j];
                
                // まだ接続されていない駅ペアを接続
                if (!field.is_connected(s1, s2)) {
                    int rail_cost = (abs(s1.r - s2.r) + abs(s1.c - s2.c) - 1) * 100;
                    if (money >= rail_cost) {
                        connect_stations(s1, s2);
                    }
                }
            }
        }
    }

public:
    // コンストラクタ
    Solver(int grid_size, int num_people, int initial_money, int turns) 
        : n(grid_size), m(num_people), k(initial_money), t(turns), 
          field(grid_size), money(initial_money) {}
    
    // 通勤者を追加
    void add_person(const Pos& home, const Pos& work) {
        people.emplace_back(home, work);
    }
    
    // メインの解法
    void solve() {
        // 通勤者を距離でソート
        sort(people.begin(), people.end());

        // 建設フェーズ（ターン数の60%まで）
        while (money >= 5000 && actions.size() < t * 0.6) {  
            bool built = false;
            
            // 駅の候補地点を毎回再計算（状況の変化を反映）
            auto station_candidates = calculate_station_importance();
            
            // 最も重要な未使用の駅候補を探す
            for (const auto& candidate : station_candidates) {
                if (field.can_build(candidate.pos, STATION)) {
                    int remaining_turns = t - actions.size();
                    
                    // 改善された建設判断を使用
                    if (should_build_station(candidate, remaining_turns)) {
                        build_station(candidate.pos);
                        built = true;
                        
                        // 駅を建設したら近くの駅と接続
                        connect_nearby_stations();
                        break;
                    }
                }
            }
            
            // 建設できなかった場合は終了
            if (!built) break;
            
            // 一時的な収入を得る（建設の余裕を作る）
            money += calculate_income();
        }
        
        // 残りのターンは待機して収入を得る
        while (actions.size() < t) {
            actions.emplace_back();
            money += calculate_income();
        }
    }
    // 結果の出力
    void output() const {
        for (const auto& action : actions) {
            action.output();
        }
        cerr << "Final money: " << money << endl;
    }

private:
    // 駅間の適切な距離を計算
    double calculate_spacing_score(const Pos& pos) const {
        vector<Pos> existing_stations;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (field.get_cell(Pos(r, c)) == STATION) {
                    existing_stations.emplace_back(r, c);
                }
            }
        }
        
        if (existing_stations.empty()) return 1.0;  // 最初の駅
        
        // 最も近い駅との距離
        double min_dist = 1e9;
        for (const auto& station : existing_stations) {
            min_dist = min(min_dist, (double)pos.manhattan_distance(station));
        }
        
        // 理想的な駅間距離（5マス程度）からの評価
        const double ideal_distance = 5.0;
        if (min_dist < 3.0) return 0.0;  // 近すぎる
        if (min_dist > 8.0) return 0.8;  // 遠すぎる
        return 1.0 - fabs(min_dist - ideal_distance) / ideal_distance;
    }
    
    // カバレッジスコアの計算（他の駅とのカバー重複を考慮）
    double calculate_coverage_score(const Pos& pos, vector<int>& unique_covered) {
        set<int> covered;
        double score = 0.0;
        
        for (int i = 0; i < people.size(); i++) {
            const auto& person = people[i];
            bool is_unique = true;
            
            if (pos.is_within_station_range(person.home)) {
                covered.insert(i);
                // 他の駅でカバーされているかチェック
                vector<Pos> stations = field.collect_stations(person.home);
                if (!stations.empty()) is_unique = false;
            }
            if (pos.is_within_station_range(person.workplace)) {
                covered.insert(i);
                vector<Pos> stations = field.collect_stations(person.workplace);
                if (!stations.empty()) is_unique = false;
            }
            
            if (is_unique) {
                unique_covered.push_back(i);
                score += person.distance;  // ユニークなカバーには通常の重み
            } else {
                score += person.distance * 0.5;  // 重複カバーには半分の重み
            }
        }
        
        return score;
    }
    
    // 改善された駅の重要度計算
    vector<StationCandidate> calculate_station_importance() {
        vector<StationCandidate> candidates;
        
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                Pos pos(r, c);
                StationCandidate candidate(pos);
                vector<int> unique_covered;
                
                // 基本スコアの計算（収入ベース）
                double base_score = 0.0;
                vector<int> covered;
                for (int i = 0; i < people.size(); i++) {
                    const auto& person = people[i];
                    if (pos.is_within_station_range(person.home) ||
                        pos.is_within_station_range(person.workplace)) {
                        base_score += person.distance;
                        covered.push_back(i);
                    }
                }
                
                if (base_score > 0) {
                    candidate.score = base_score;
                    candidate.covered_people = covered;
                    candidate.spacing_score = calculate_spacing_score(pos);
                    candidate.coverage_score = calculate_coverage_score(pos, unique_covered);
                    candidate.unique_covered_people.insert(
                        unique_covered.begin(), unique_covered.end());
                    candidates.push_back(candidate);
                }
            }
        }
        
        sort(candidates.begin(), candidates.end());
        return candidates;
    }
    
    // 投資判断の改善
    bool should_build_station(const StationCandidate& candidate, int remaining_turns) {
        // 基本的な収益性チェック
        double potential_income = 0;
        for (int idx : candidate.covered_people) {
            potential_income += people[idx].distance;
        }
        
        // ユニークカバーへのボーナス
        double unique_bonus = 0;
        for (int idx : candidate.unique_covered_people) {
            unique_bonus += people[idx].distance * 0.3;  // 30%ボーナス
        }
        
        // 投資回収期間の計算
        double total_potential = potential_income + unique_bonus;
        int payback_turns = ceil(5000.0 / total_potential);
        
        // 建設判断
        if (payback_turns > remaining_turns) return false;
        if (candidate.spacing_score < 0.3) return false;  // 駅が近すぎる
        if (candidate.total_score() < remaining_turns * 0.01) return false;  // スコアが低すぎる
        
        return true;
    }

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 入力
    int n, m, k, t;
    cin >> n >> m >> k >> t;
    
    Solver solver(n, m, k, t);
    
    // 通勤者の情報を入力
    for (int i = 0; i < m; i++) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        solver.add_person(Pos(r1, c1), Pos(r2, c2));
    }
    
    // 解を求める
    solver.solve();
    
    // 出力
    solver.output();
    
    return 0;
}