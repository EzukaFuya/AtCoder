#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> ans;
    auto dfs = [&](auto dfs, vector<int> v) -> void {
        int sz = v.size();
        if (sz == N) {
            ans.push_back(v);
            return;
        }
        else {
            for (int i = (sz == 0 ? 1 : v.back() + 10); i <= M - 10 * (N - sz -1); i++) {
                vector<int> nxt = v;
                nxt.push_back(i);
                dfs(dfs, nxt);
            }
        }
    };
    
    dfs(dfs, {});
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < N; j++) {
            cout << ans[i][j];
            if (j != N - 1) cout << " ";
        }
        cout << endl;
    }
    
    return 0;
}