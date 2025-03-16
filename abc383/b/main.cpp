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

    int counter = 0;
    for (int i1 = 0; i1 < H; i1++) {
        for (int j1 = 0; j1 < W; j1++) {
            if (S[i1][j1] == '.') {
                for (int i2 = 0; i2 < H; i2++) {
                    for (int j2 = 0; j2 < W; j2++) {
                        if (S[i2][j2] == '.' && !(i1 == i2 && j1 == j2)) {
                            int wet_counter = 0;
                            for (int i = 0; i < H; i ++) {
                                for (int j = 0; j < W; j++) {
                                    if (S[i][j] == '.' && 
                                        (manhattan_distance(i1, j1, i, j) <= D || 
                                         manhattan_distance(i2, j2, i, j) <= D)) {
                                            wet_counter++;
                                    }
                                }
                            }
                            counter = max(counter, wet_counter);
                        }
                    }
                }
            }
        }
    }
    cout << counter << endl;
    return 0;
}