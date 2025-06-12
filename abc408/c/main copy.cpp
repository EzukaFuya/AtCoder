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

    vector<pair<int, int>> turrets(M);
    for (int i = 0; i < M; i++) {
        int l, r;
        cin >> l >> r;
        turrets[i] = {l, r};
    }

    sort(turrets.begin(), turrets.end());
    int left = turrets[0].first;
    int right = turrets[1].first;
    int min_attack_num = INT_MAX;
    int counter = 0;
    while(right < N) {
        if (left < right) counter++;
        min_attack_num = min(min_attack_num, counter);
        right++;
    }
    cout << min_attack_num << endl;
    return 0;
}
