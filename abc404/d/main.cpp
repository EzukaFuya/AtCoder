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

    vector<int> cost(N);
    for (int i = 0; i < N; i++) {
        cin >> cost[i];
    }

    // animals_zoo[i] = list of animals in zoo i
    // zoo_animals[i] = list of zoos where animal i is present
    vector<vector<int>> animals_zoo(M);
    vector<vector<int>> zoo_animals(N);
    for (int i = 0; i < M; i++) {
        int K;
        cin >> K;
        for (int j = 0; j < K; j++) {
            int A;
            cin >> A;
            A--;
            animals_zoo[i].push_back(A);
            zoo_animals[A].push_back(i);
        }
    }

    ll ans = 1e18;
    
    for (int S = 0; S < (1 << (2 * N)); S++) {
        vector<int> cnt(M, 0);
        ll cost_ = 0;

        for (int i = 0; i < 2 * N; i++) {
            if (S >> i & 1) {
                int zoo = i / 2;
                for (auto& animal : zoo_animals[zoo]) {
                    cnt[animal]++;
                }
                cost_ += cost[zoo];
            }
        }

        if (*min_element(cnt.begin(), cnt.end()) >= 2) {
            ans = min(ans, cost_);
        }
    }

    cout << ans << endl;

    return 0;
}
