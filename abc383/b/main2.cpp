#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int manhattan_distance(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) + abs(c1 - c2);
}

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W, D;
    cin >> H >> W >> D;

    vector<string> S(H);
    for (int i = 0; i < H; i++) {
        cin >> S[i];
    }

    vector<pair<int, int>> floor_cells;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (S[i][j] == '.') {
                floor_cells.push_back({i, j});
            }
        }
    }

    int wet_cells_count = 0;
    for (int i = 0; i < floor_cells.size(); i++) {
        for (int j = i; j < floor_cells_size(); j++) {
            auto [i1, j1] = floor_cells[i];
            auto [i2, j2] = floor_cells[j];

            int wet_counter = 0;
            for (auto [x, y]: floor_cells) {
                if (manhattan_distance(i1, j1, x, y) <= D || manhattan_distance(i2, j2, x, y) <= D) {
                    wet_counter++;
                }
            }
            wet_cells_count = max(wet_cells_count, wet_counter);
        }
    }

    cout << wet_cells_count << endl;
    return 0;
}