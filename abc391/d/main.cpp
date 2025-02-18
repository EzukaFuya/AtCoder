#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, W;
    cin >> N >> W;

    // 各列のブロックを管理
    vector<vector<pair<int, int>>> blocks(W + 1);  // {y座標, ブロック番号}
    vector<int> X(N), Y(N);
    
    for (int i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];
        blocks[X[i]].push_back({Y[i], i});
    }

    // 各ブロックがその列の下から何番目かを記録
    vector<int> cnt(N);
    // 下からi番目のブロックが消える時刻
    vector<ll> disappear(N + 1, -1);
    
    // 各列について処理
    for (int x = 1; x <= W; x++) {
        // y座標でソート
        sort(blocks[x].begin(), blocks[x].end());
        
        // その列の各ブロックについて
        for (int j = 0; j < blocks[x].size(); j++) {
            int block_id = blocks[x][j].second;
            cnt[block_id] = j;  // そのブロックが下から何番目か
            // j番目のブロックが消える時刻を更新
            disappear[j] = max(disappear[j], (ll)blocks[x][j].first);
        }
        disappear[blocks[x].size()] = 1e10;
    }

    // 下のブロックが消えた後に上のブロックが落ちてくる時間を考慮
    for (int i = 0; i < N; i++) {
        disappear[i + 1] = max(disappear[i + 1], disappear[i] + 1);
    }

    int Q;
    cin >> Q;
    
    while (Q--) {
        ll T, A;
        cin >> T >> A;
        A--;
        cout << (T < disappear[cnt[A]] ? "Yes" : "No") << endl;
    }

    return 0;
}