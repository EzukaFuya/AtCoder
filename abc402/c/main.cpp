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

    vector<vector<ll>> Food(M);
    vector<vector<ll>> Ingredient(N);
    vector<int> cnt(M);
    for (int i = 0; i < M; i++) {
        int K;
        cin >> K;
        Food[i].resize(K);
        cnt[i] = K;
        for (int j = 0; j < K; j++) {
            cin >> Food[i][j];
            Food[i][j]--;
            Ingredient[Food[i][j]].push_back(i); 
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        int B;
        cin >> B;
        B--;
        for (auto food : Ingredient[B]) {
            cnt[food]--;
            if (cnt[food] == 0) {
                ans++;
            }
        }
        cout << ans << endl;
    }

    return 0;
}