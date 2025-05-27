#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<pair<int, int>> P(N);
    vector<int> Q(N);

    for (int i = 0; i < N; i++) {
        cin >> P[i].first;
        P[i].second = i;
    }

    sort(P.begin(), P.end(), greater<pair<int, int>>());
    
    int rank = 1;
    Q[P[0].second] = rank;
    for (int i = 1; i < N; i++) {
        if (P[i].first < P[i - 1].first) {
            rank = i + 1;
        }
        Q[P[i].second] = rank;
    }

    for (int i = 0; i < N; i++) {
        cout << Q[i] <<endl;
    }

    return 0;
}