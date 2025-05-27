#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

ll max_score = 0;

void dfs(int pos, vector<vector<bool>> used, ll curr_xor, int H, int W, vector<vector<ll>> A) {
    if (pos == H * W) {
        max_score = max(max_score, curr_xor);
        return;
    }

    int i = pos / W;
    int j = pos % W;

    if (used[i][j]) {
        dfs(pos + 1, used, curr_xor, H, W, A);
        return;
    }

    /* Don't put domino */
    dfs(pos+1, used, curr_xor ^ A[i][j], H, W, A);

    /* Put domino x */
    if (i + 1 < H && used[i + 1][j] == false) {
        used[i][j] = true;
        used[i + 1][j] = true;
        dfs(pos + 1, used, curr_xor, H, W, A);
        used[i][j] = false;
        used[i + 1][j] = false; 
    }

    /* Put domino y */
    if (j + 1 < W && used[i][j + 1] == false) {
        used[i][j] = true;
        used[i][j + 1] = true;
        dfs(pos + 1, used, curr_xor, H, W, A);
        used[i][j] = false;
        used[i][j + 1] = false;
    }
}

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W;
    cin >> H >> W;

    vector<vector<ll>> A(H, vector<ll>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> A[i][j];
        }
    }

    vector<vector<bool>> used(H, vector<bool>(W, false));
    dfs(0, used, 0, H, W, A);

    cout << max_score <<endl;
    return 0;
}
