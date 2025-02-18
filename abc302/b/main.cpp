#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    for (int i = 0; i < H; i++) {
        cin >> S[i];
    }

    vector<pair<int, int> > ans;
    string target1 = "snuke";
    string target2 = "ekuns";
    
    // 横
    for (int i = 0; i < H; i++) {
        for (int j = 0; j <= W - 5; j++) {
            bool is_snake = true;
            for (int k = 0; k < 5; k++) {
                if (S[i][j + k] != target1[k]) {
                    is_snake = false;
                    break;
                }
            }
            if (is_snake) {
                for (int k = 0; k < 5; k++) {
                    ans.push_back(make_pair(i + 1, j + k + 1));
                }
            }
            
            is_snake = true;
            for (int k = 0; k < 5; k++) {
                if (S[i][j + k] != target2[k]) {
                    is_snake = false;
                    break;
                }
            }
            if (is_snake) {
                for (int k = 4; k >= 0; k--) {
                    ans.push_back(make_pair(i + 1, j + k + 1));
                }
            }
        }
    }

    // 縦
    for (int i = 0; i <= H - 5; i++) {
        for (int j = 0; j < W; j++) {
            bool is_snake = true;
            for (int k = 0; k < 5; k++) {
                if (S[i + k][j] != target1[k]) {
                    is_snake = false;
                    break;
                }
            }
            if (is_snake) {
                for (int k = 0; k < 5; k++) {
                    ans.push_back(make_pair(i + k + 1, j + 1));
                }
            }

            is_snake = true;
            for (int k = 0; k < 5; k++) {
                if (S[i + k][j] != target2[k]) {
                    is_snake = false;
                    break;
                }
            }
            if (is_snake) {
                for (int k = 4; k >= 0; k--) {
                    ans.push_back(make_pair(i + k + 1, j + 1));
                }
            }
        }
    }

    // 斜め（右下と左下）
    for (int i = 0; i <= H - 5; i++) {
        for (int j = 0; j <= W - 5; j++) {
            // 右下
            bool is_snake = true;
            for (int k = 0; k < 5; k++) {
                if (S[i + k][j + k] != target1[k]) {
                    is_snake = false;
                    break;
                }
            }
            if (is_snake) {
                for (int k = 0; k < 5; k++) {
                    ans.push_back(make_pair(i + k + 1, j + k + 1));
                }
            }

            is_snake = true;
            for (int k = 0; k < 5; k++) {
                if (S[i + k][j + k] != target2[k]) {
                    is_snake = false;
                    break;
                }
            }
            if (is_snake) {
                for (int k = 4; k >= 0; k--) {
                    ans.push_back(make_pair(i + k + 1, j + k + 1));
                }
            }
        }
    }

    // 斜め（右上と左上）
    for (int i = 4; i < H; i++) {
        for (int j = 0; j <= W - 5; j++) {
            // 右上
            bool is_snake = true;
            for (int k = 0; k < 5; k++) {
                if (S[i - k][j + k] != target1[k]) {
                    is_snake = false;
                    break;
                }
            }
            if (is_snake) {
                for (int k = 0; k < 5; k++) {
                    ans.push_back(make_pair(i - k + 1, j + k + 1));
                }
            }

            is_snake = true;
            for (int k = 0; k < 5; k++) {
                if (S[i - k][j + k] != target2[k]) {
                    is_snake = false;
                    break;
                }
            }
            if (is_snake) {
                for (int k = 4; k >= 0; k--) {
                    ans.push_back(make_pair(i - k + 1, j + k + 1));
                }
            }
        }
    }

    if (!ans.empty()) {
        for (int i = 0; i < 5; i++) {
            cout << ans[i].first << " " << ans[i].second << endl;
        }
    }

    return 0;
}